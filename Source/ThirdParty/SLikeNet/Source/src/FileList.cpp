/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/FileList.h"

#if _RAKNET_SUPPORT_FileOperations==1

#include <stdio.h> // RAKNET_DEBUG_PRINTF
#include "slikenet/assert.h"
#if defined(__ANDROID__)
#include <asm/io.h>
#elif defined(_WIN32) || defined(__CYGWIN__)
#include <io.h>


#elif !defined ( __APPLE__ ) && !defined ( __APPLE_CC__ ) && !defined ( __PPC__ ) && !defined ( __FreeBSD__ ) && !defined ( __S3E__ )
#include <sys/io.h>
#endif


#ifdef _WIN32 
// For mkdir
#include <direct.h>


#else
#include <sys/stat.h>
#endif

//#include "slikenet/DR_SHA1.h"
#include "slikenet/DS_Queue.h"
#include "slikenet/StringCompressor.h"
#include "slikenet/BitStream.h"
#include "slikenet/FileOperations.h"
#include "slikenet/SuperFastHash.h"
#include "slikenet/assert.h"
#include "slikenet/LinuxStrings.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

#define MAX_FILENAME_LENGTH 512
static const unsigned HASH_LENGTH=4;

using namespace SLNet;

// alloca

#if   defined(_WIN32)
#include <malloc.h>


#else
	#if !defined ( __FreeBSD__ )
	#include <alloca.h>
	#endif
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "slikenet/_FindFirst.h"
#include <stdint.h> //defines intptr_t
#endif

#include "slikenet/alloca.h"

//int RAK_DLL_EXPORT FileListNodeComp( char * const &key, const FileListNode &data )
//{
//	return strcmp(key, data.filename);
//}


STATIC_FACTORY_DEFINITIONS(FileListProgress,FileListProgress)
STATIC_FACTORY_DEFINITIONS(FLP_Printf,FLP_Printf)
STATIC_FACTORY_DEFINITIONS(FileList,FileList)

/// First callback called when FileList::AddFilesFromDirectory() starts
void FLP_Printf::OnAddFilesFromDirectoryStarted(FileList *fileList, char *dir) {
	(void) fileList;
	RAKNET_DEBUG_PRINTF("Adding files from directory %s\n",dir);}

/// Called for each directory, when that directory begins processing
void FLP_Printf::OnDirectory(FileList *fileList, char *dir, unsigned int directoriesRemaining) {
	(void) fileList;
	RAKNET_DEBUG_PRINTF("Adding %s. %i remaining.\n", dir, directoriesRemaining);}	
void FLP_Printf::OnFilePushesComplete( SystemAddress systemAddress, unsigned short setID )
{
	(void) setID;

	char str[32];
	systemAddress.ToString(true, (char*) str, static_cast<size_t>(32));
	RAKNET_DEBUG_PRINTF("File pushes complete to %s\n", str);	
}
void FLP_Printf::OnSendAborted( SystemAddress systemAddress )
{
	char str[32];
	systemAddress.ToString(true, (char*) str, static_cast<size_t>(32));
	RAKNET_DEBUG_PRINTF("Send aborted to %s\n", str);
}
FileList::FileList()
{
}
FileList::~FileList()
{
	Clear();
}
void FileList::AddFile(const char *filepath, const char *filename, FileListNodeContext context)
{
	if (filepath==0 || filename==0)
		return;

	char *data;
	//std::fstream file;
	//file.open(filename, std::ios::in | std::ios::binary);

	FILE *fp;
	if (fopen_s(&fp, filepath, "rb") != 0)
		return;
	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (length > (int) ((unsigned int)-1 / 8))
	{
		// If this assert hits, split up your file. You could also change BitSize_t in types.h to unsigned long long but this is not recommended for performance reasons
		RakAssert("Cannot add files over 536 MB" && 0);
		fclose(fp);
		return;
	}


#if USE_ALLOCA==1
	bool usedAlloca=false;
	if (length < MAX_ALLOCA_STACK_ALLOCATION)
	{
		data = ( char* ) alloca( length );
		usedAlloca=true;
	}
	else
#endif
	{
		data = (char*) rakMalloc_Ex( length, _FILE_AND_LINE_ );
		RakAssert(data);
	}

	fread(data, 1, length, fp);
	AddFile(filename, filepath, data, length, length, context);
	fclose(fp);

#if USE_ALLOCA==1
	if (usedAlloca==false)
#endif
		rakFree_Ex(data, _FILE_AND_LINE_ );

}
void FileList::AddFile(const char *filename, const char *fullPathToFile, const char *data, const unsigned dataLength, const unsigned fileLength, FileListNodeContext context, bool isAReference, bool takeDataPointer)
{
	if (filename==0)
		return;
	if (strlen(filename)>MAX_FILENAME_LENGTH)
	{
		// Should be enough for anyone
		RakAssert(0);
		return;
	}
	// If adding a reference, do not send data
	RakAssert(isAReference==false || data==0);
	// Avoid duplicate insertions unless the data is different, in which case overwrite the old data
	unsigned i;
	for (i=0; i<fileList.Size();i++)
	{
		if (strcmp(fileList[i].filename, filename)==0)
		{
			if (fileList[i].fileLengthBytes==fileLength && fileList[i].dataLengthBytes==dataLength &&
				(dataLength==0 || fileList[i].data==0 ||
				memcmp(fileList[i].data, data, dataLength)==0
				))
				// Exact same file already here
				return;

			// File of the same name, but different contents, so overwrite
			rakFree_Ex(fileList[i].data, _FILE_AND_LINE_ );
			fileList.RemoveAtIndex(i);
			break;
		}
	}

	FileListNode n;
//	size_t fileNameLen = strlen(filename);
	if (dataLength && data)
	{
		if (takeDataPointer)
		{
			n.data=(char*) data;
		}
		else
		{
			n.data=(char*) rakMalloc_Ex( dataLength, _FILE_AND_LINE_ );
			RakAssert(n.data);
			memcpy(n.data, data, dataLength);
		}
	}
	else
		n.data=0;
	n.dataLengthBytes=dataLength;
	n.fileLengthBytes=fileLength;
	n.isAReference=isAReference;
	n.context=context;
	if (n.context.dataPtr==0)
		n.context.dataPtr=n.data;
	if (n.context.dataLength==0)
		n.context.dataLength=dataLength;
	n.filename=filename;
	n.fullPathToFile=fullPathToFile;
		
	fileList.Insert(n, _FILE_AND_LINE_);
}
void FileList::AddFilesFromDirectory(const char *applicationDirectory, const char *subDirectory, bool writeHash, bool writeData, bool recursive, FileListNodeContext context)
{



	DataStructures::Queue<char*> dirList;
	char root[260];
	char fullPath[520];
	_finddata_t fileInfo;
	intptr_t dir;
	FILE *fp;
	char *dirSoFar, *fileData;
	dirSoFar=(char*) rakMalloc_Ex( 520, _FILE_AND_LINE_ );
	RakAssert(dirSoFar);

	if (applicationDirectory)
		strcpy_s(root, applicationDirectory);
	else
		root[0]=0;

	int rootLen=(int)strlen(root);
	if (rootLen)
	{
		strcpy_s(dirSoFar, 520, root);
		if (FixEndingSlash(dirSoFar, 520))
			rootLen++;
	}
	else
		dirSoFar[0]=0;
	
	if (subDirectory)
	{
		strcat_s(dirSoFar, 520, subDirectory);
		FixEndingSlash(dirSoFar, 520);
	}
	for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
		fileListProgressCallbacks[flpcIndex]->OnAddFilesFromDirectoryStarted(this, dirSoFar);
	// RAKNET_DEBUG_PRINTF("Adding files from directory %s\n",dirSoFar);
	dirList.Push(dirSoFar, _FILE_AND_LINE_ );
	while (dirList.Size())
	{
		dirSoFar=dirList.Pop();
		strcpy_s(fullPath, dirSoFar);
		// Changed from *.* to * for Linux compatibility
		strcat_s(fullPath, "*");


                dir=_findfirst(fullPath, &fileInfo );
		if (dir==-1)
		{
			_findclose(dir);
			rakFree_Ex(dirSoFar, _FILE_AND_LINE_ );
			unsigned i;
			for (i=0; i < dirList.Size(); i++)
				rakFree_Ex(dirList[i], _FILE_AND_LINE_ );
			return;
		}

//		RAKNET_DEBUG_PRINTF("Adding %s. %i remaining.\n", fullPath, dirList.Size());
		for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
			fileListProgressCallbacks[flpcIndex]->OnDirectory(this, fullPath, dirList.Size());

        do
		{
                    // no guarantee these entries are first...
                    if (strcmp("." , fileInfo.name) == 0 ||
                        strcmp("..", fileInfo.name) == 0)
                    {
                        continue;
                    }
                    
			if ((fileInfo.attrib & (_A_HIDDEN | _A_SUBDIR | _A_SYSTEM))==0)
			{
				strcpy_s(fullPath, dirSoFar);
				strcat_s(fullPath, fileInfo.name);
				fileData=0;

				for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
					fileListProgressCallbacks[flpcIndex]->OnFile(this, dirSoFar, fileInfo.name, fileInfo.size);

				if (writeData && writeHash)
				{
					if (fopen_s(&fp, fullPath, "rb") == 0)
					{
						fileData= (char*) rakMalloc_Ex( fileInfo.size+HASH_LENGTH, _FILE_AND_LINE_ );
						RakAssert(fileData);
						fread(fileData+HASH_LENGTH, fileInfo.size, 1, fp);
						fclose(fp);

						unsigned int hash = SuperFastHash(fileData+HASH_LENGTH, fileInfo.size);
						if (SLNet::BitStream::DoEndianSwap())
							SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash, sizeof(hash));
						memcpy(fileData, &hash, HASH_LENGTH);

						//					sha1.Reset();
						//					sha1.Update( ( unsigned char* ) fileData+HASH_LENGTH, fileInfo.size );
						//					sha1.Final();
						//					memcpy(fileData, sha1.GetHash(), HASH_LENGTH);
						// File data and hash
						AddFile((const char*)fullPath+rootLen, fullPath, fileData, fileInfo.size+HASH_LENGTH, fileInfo.size, context);
					}					
				}
				else if (writeHash)
				{
//					sha1.Reset();
//					DR_SHA1.hashFile((char*)fullPath);
//					sha1.Final();

					unsigned int hash = SuperFastHashFile(fullPath);
					if (SLNet::BitStream::DoEndianSwap())
						SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash, sizeof(hash));

					// Hash only
				//	AddFile((const char*)fullPath+rootLen, (const char*)sha1.GetHash(), HASH_LENGTH, fileInfo.size, context);
					AddFile((const char*)fullPath+rootLen, fullPath, (const char*)&hash, HASH_LENGTH, fileInfo.size, context);
				}
				else if (writeData)
				{
					fileData= (char*) rakMalloc_Ex( fileInfo.size, _FILE_AND_LINE_ );
					RakAssert(fileData);
					fopen_s(&fp, fullPath, "rb");
					fread(fileData, fileInfo.size, 1, fp);
					fclose(fp);

					// File data only
					AddFile(fullPath+rootLen, fullPath, fileData, fileInfo.size, fileInfo.size, context);
				}
				else
				{
					// Just the filename
					AddFile(fullPath+rootLen, fullPath, 0, 0, fileInfo.size, context);
				}

				if (fileData)
					rakFree_Ex(fileData, _FILE_AND_LINE_ );
			}
			else if ((fileInfo.attrib & _A_SUBDIR) && (fileInfo.attrib & (_A_HIDDEN | _A_SYSTEM))==0 && recursive)
			{
				char *newDir=(char*) rakMalloc_Ex( 520, _FILE_AND_LINE_ );
				RakAssert(newDir);
				strcpy_s(newDir, 520, dirSoFar);
				strcat_s(newDir, 520, fileInfo.name);
				strcat_s(newDir, 520, "/");
				dirList.Push(newDir, _FILE_AND_LINE_ );
			}

		} while (_findnext(dir, &fileInfo ) != -1);

		_findclose(dir);
		rakFree_Ex(dirSoFar, _FILE_AND_LINE_ );
	}

}
void FileList::Clear(void)
{
	unsigned i;
	for (i=0; i<fileList.Size(); i++)
	{
		rakFree_Ex(fileList[i].data, _FILE_AND_LINE_ );
	}
	fileList.Clear(false, _FILE_AND_LINE_);
}
void FileList::Serialize(SLNet::BitStream *outBitStream)
{
	outBitStream->WriteCompressed(fileList.Size());
	unsigned i;
	for (i=0; i < fileList.Size(); i++)
	{
		outBitStream->WriteCompressed(fileList[i].context.op);
		outBitStream->WriteCompressed(fileList[i].context.flnc_extraData1);
		outBitStream->WriteCompressed(fileList[i].context.flnc_extraData2);
		StringCompressor::Instance()->EncodeString(fileList[i].filename.C_String(), MAX_FILENAME_LENGTH, outBitStream);

		bool writeFileData = (fileList[i].dataLengthBytes>0)==true;
		outBitStream->Write(writeFileData);
		if (writeFileData)
		{
			outBitStream->WriteCompressed(fileList[i].dataLengthBytes);
			outBitStream->Write(fileList[i].data, fileList[i].dataLengthBytes);
		}

		outBitStream->Write((bool)(fileList[i].fileLengthBytes==fileList[i].dataLengthBytes));
		if (fileList[i].fileLengthBytes!=fileList[i].dataLengthBytes)
			outBitStream->WriteCompressed(fileList[i].fileLengthBytes);
	}
}
bool FileList::Deserialize(SLNet::BitStream *inBitStream)
{
	bool b, dataLenNonZero=false, fileLenMatchesDataLen=false;
	char filename[512];
	uint32_t fileListSize;
	FileListNode n;
	b=inBitStream->ReadCompressed(fileListSize);
#ifdef _DEBUG
	RakAssert(b);
	RakAssert(fileListSize < 10000);
#endif
	if (b==false || fileListSize > 10000)
		return false; // Sanity check
	Clear();	
	unsigned i;
	for (i=0; i < fileListSize; i++)
	{
		inBitStream->ReadCompressed(n.context.op);
		inBitStream->ReadCompressed(n.context.flnc_extraData1);
		inBitStream->ReadCompressed(n.context.flnc_extraData2);
		StringCompressor::Instance()->DecodeString((char*)filename, MAX_FILENAME_LENGTH, inBitStream);
		inBitStream->Read(dataLenNonZero);
		if (dataLenNonZero)
		{
			inBitStream->ReadCompressed(n.dataLengthBytes);
			// sanity check
			if (n.dataLengthBytes>2000000000)
			{
#ifdef _DEBUG
				RakAssert(n.dataLengthBytes<=2000000000);
#endif
				return false;
			}
			n.data=(char*) rakMalloc_Ex( (size_t) n.dataLengthBytes, _FILE_AND_LINE_ );
			RakAssert(n.data);
			inBitStream->Read(n.data, n.dataLengthBytes);
		}
		else
		{
			n.dataLengthBytes=0;
			n.data=0;
		}
		
		b=inBitStream->Read(fileLenMatchesDataLen);
		if (fileLenMatchesDataLen)
			n.fileLengthBytes=(unsigned) n.dataLengthBytes;
		else
			b=inBitStream->ReadCompressed(n.fileLengthBytes);
#ifdef _DEBUG
		RakAssert(b);
#endif
		if (b==0)
		{
			Clear();
			return false;
		}
		n.filename=filename;
		n.fullPathToFile=filename;
		fileList.Insert(n, _FILE_AND_LINE_);
	}

	return true;
}
void FileList::GetDeltaToCurrent(FileList *input, FileList *output, const char *dirSubset, const char *remoteSubdir)
{
	// For all files in this list that do not match the input list, write them to the output list.
	// dirSubset allows checking only a portion of the files in this list.
	unsigned thisIndex, inputIndex;
	unsigned dirSubsetLen, localPathLen, remoteSubdirLen;
	bool match;
	if (dirSubset)
		dirSubsetLen = (unsigned int) strlen(dirSubset);
	else
		dirSubsetLen = 0;
	if (remoteSubdir && remoteSubdir[0])
	{
		remoteSubdirLen=(unsigned int) strlen(remoteSubdir);
		if (IsSlash(remoteSubdir[remoteSubdirLen-1]))
			remoteSubdirLen--;
	}
	else
		remoteSubdirLen=0;

	for (thisIndex=0; thisIndex < fileList.Size(); thisIndex++)
	{
		localPathLen = (unsigned int) fileList[thisIndex].filename.GetLength();
		while (localPathLen>0)
		{
			if (IsSlash(fileList[thisIndex].filename[localPathLen-1]))
			{
				localPathLen--;
				break;
			}
			localPathLen--;
		}

		// fileList[thisIndex].filename has to match dirSubset and be shorter or equal to it in length.
		if (dirSubsetLen>0 &&
			(localPathLen<dirSubsetLen ||
			_strnicmp(fileList[thisIndex].filename.C_String(), dirSubset, dirSubsetLen)!=0 ||
			(localPathLen>dirSubsetLen && IsSlash(fileList[thisIndex].filename[dirSubsetLen])==false)))
			continue;

		match=false;
		for (inputIndex=0; inputIndex < input->fileList.Size(); inputIndex++)
		{
			// If the filenames, hashes, and lengths match then skip this element in fileList.  Otherwise write it to output
			if (_stricmp(input->fileList[inputIndex].filename.C_String()+remoteSubdirLen,fileList[thisIndex].filename.C_String()+dirSubsetLen)==0)
			{
				match=true;
				if (input->fileList[inputIndex].fileLengthBytes==fileList[thisIndex].fileLengthBytes &&
					input->fileList[inputIndex].dataLengthBytes==fileList[thisIndex].dataLengthBytes &&
					memcmp(input->fileList[inputIndex].data,fileList[thisIndex].data,(size_t) fileList[thisIndex].dataLengthBytes)==0)
				{
					// File exists on both machines and is the same.
					break;
				}
				else
				{
					// File exists on both machines and is not the same.
					output->AddFile(fileList[thisIndex].filename, fileList[thisIndex].fullPathToFile, 0,0, fileList[thisIndex].fileLengthBytes, FileListNodeContext(0,0,0,0), false);
					break;
				}
			}
		}
		if (match==false)
		{
            // Other system does not have the file at all
			output->AddFile(fileList[thisIndex].filename, fileList[thisIndex].fullPathToFile, 0,0, fileList[thisIndex].fileLengthBytes, FileListNodeContext(0,0,0,0), false);
		}
	}
}
void FileList::ListMissingOrChangedFiles(const char *applicationDirectory, FileList *missingOrChangedFiles, bool alwaysWriteHash, bool neverWriteHash)
{
	unsigned fileLength;
//	CSHA1 sha1;
	FILE *fp;
	char fullPath[512];
	unsigned i;
//	char *fileData;

	for (i=0; i < fileList.Size(); i++)
	{
		strcpy_s(fullPath, applicationDirectory);
		FixEndingSlash(fullPath, 512);
		strcat_s(fullPath,fileList[i].filename);
		if (fopen_s(&fp, fullPath, "rb") != 0)
		{
			missingOrChangedFiles->AddFile(fileList[i].filename, fileList[i].fullPathToFile, 0, 0, 0, FileListNodeContext(0,0,0,0), false);
		}
		else
		{
			fseek(fp, 0, SEEK_END);
			fileLength = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			if (fileLength != fileList[i].fileLengthBytes && alwaysWriteHash==false)
			{
				missingOrChangedFiles->AddFile(fileList[i].filename, fileList[i].fullPathToFile, 0, 0, fileLength, FileListNodeContext(0,0,0,0), false);
			}
			else
			{

//				fileData= (char*) rakMalloc_Ex( fileLength, _FILE_AND_LINE_ );
//				fread(fileData, fileLength, 1, fp);

//				sha1.Reset();
//				sha1.Update( ( unsigned char* ) fileData, fileLength );
//				sha1.Final();

//				rakFree_Ex(fileData, _FILE_AND_LINE_ );

				unsigned int hash = SuperFastHashFilePtr(fp);
				if (SLNet::BitStream::DoEndianSwap())
					SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash, sizeof(hash));

				//if (fileLength != fileList[i].fileLength || memcmp( sha1.GetHash(), fileList[i].data, HASH_LENGTH)!=0)
				if (fileLength != fileList[i].fileLengthBytes || memcmp( &hash, fileList[i].data, HASH_LENGTH)!=0)
				{
					if (neverWriteHash==false)
					//	missingOrChangedFiles->AddFile((const char*)fileList[i].filename, (const char*)sha1.GetHash(), HASH_LENGTH, fileLength, 0);
						missingOrChangedFiles->AddFile((const char*)fileList[i].filename, (const char*)fileList[i].fullPathToFile, (const char *) &hash, HASH_LENGTH, fileLength, FileListNodeContext(0,0,0,0), false);
					else
						missingOrChangedFiles->AddFile((const char*)fileList[i].filename, (const char*)fileList[i].fullPathToFile, 0, 0, fileLength, FileListNodeContext(0,0,0,0), false);
				}
			}
			fclose(fp);
		}
	}
}
void FileList::PopulateDataFromDisk(const char *applicationDirectory, bool writeFileData, bool writeFileHash, bool removeUnknownFiles)
{
	FILE *fp;
	char fullPath[512];
	unsigned i;
//	CSHA1 sha1;

	i=0;
	while (i < fileList.Size())
	{
		rakFree_Ex(fileList[i].data, _FILE_AND_LINE_ );
		strcpy_s(fullPath, applicationDirectory);
		FixEndingSlash(fullPath, 512);
		strcat_s(fullPath,fileList[i].filename.C_String());
		if (fopen_s(&fp, fullPath, "rb") == 0)
		{
			if (writeFileHash || writeFileData)
			{
				fseek(fp, 0, SEEK_END);
				fileList[i].fileLengthBytes = ftell(fp);
				fseek(fp, 0, SEEK_SET);
				if (writeFileHash)
				{
					if (writeFileData)
					{
						// Hash + data so offset the data by HASH_LENGTH
						fileList[i].data=(char*) rakMalloc_Ex( fileList[i].fileLengthBytes+HASH_LENGTH, _FILE_AND_LINE_ );
						RakAssert(fileList[i].data);
						fread(fileList[i].data+HASH_LENGTH, fileList[i].fileLengthBytes, 1, fp);
//						sha1.Reset();
//						sha1.Update((unsigned char*)fileList[i].data+HASH_LENGTH, fileList[i].fileLength);
//						sha1.Final();
						unsigned int hash = SuperFastHash(fileList[i].data+HASH_LENGTH, fileList[i].fileLengthBytes);
						if (SLNet::BitStream::DoEndianSwap())
							SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash, sizeof(hash));
//						memcpy(fileList[i].data, sha1.GetHash(), HASH_LENGTH);
						memcpy(fileList[i].data, &hash, HASH_LENGTH);
					}
					else
					{
						// Hash only
						fileList[i].dataLengthBytes=HASH_LENGTH;
						if (fileList[i].fileLengthBytes < HASH_LENGTH)
							fileList[i].data=(char*) rakMalloc_Ex( HASH_LENGTH, _FILE_AND_LINE_ );
						else
							fileList[i].data=(char*) rakMalloc_Ex( fileList[i].fileLengthBytes, _FILE_AND_LINE_ );
						RakAssert(fileList[i].data);
						fread(fileList[i].data, fileList[i].fileLengthBytes, 1, fp);
				//		sha1.Reset();
				//		sha1.Update((unsigned char*)fileList[i].data, fileList[i].fileLength);
				//		sha1.Final();
						unsigned int hash = SuperFastHash(fileList[i].data, fileList[i].fileLengthBytes);
						if (SLNet::BitStream::DoEndianSwap())
							SLNet::BitStream::ReverseBytesInPlace((unsigned char*) &hash, sizeof(hash));
						// memcpy(fileList[i].data, sha1.GetHash(), HASH_LENGTH);
						memcpy(fileList[i].data, &hash, HASH_LENGTH);
					}
				}
				else
				{
					// Data only
					fileList[i].dataLengthBytes=fileList[i].fileLengthBytes;
					fileList[i].data=(char*) rakMalloc_Ex( fileList[i].fileLengthBytes, _FILE_AND_LINE_ );
					RakAssert(fileList[i].data);
					fread(fileList[i].data, fileList[i].fileLengthBytes, 1, fp);
				}

				fclose(fp);
				i++;
			}
			else
			{
				fileList[i].data=0;
				fileList[i].dataLengthBytes=0;
			}
		}
		else
		{
			if (removeUnknownFiles)
			{
				fileList.RemoveAtIndex(i);
			}
			else
				i++;			
		}
	}
}
void FileList::FlagFilesAsReferences(void)
{
	for (unsigned int i=0; i < fileList.Size(); i++)
	{
		fileList[i].isAReference=true;
		fileList[i].dataLengthBytes=fileList[i].fileLengthBytes;
	}
}
void FileList::WriteDataToDisk(const char *applicationDirectory)
{
	char fullPath[512];
	unsigned i,j;

	for (i=0; i < fileList.Size(); i++)
	{
		strcpy_s(fullPath, applicationDirectory);
		FixEndingSlash(fullPath, 512);
		strcat_s(fullPath,fileList[i].filename.C_String());
		
		// Security - Don't allow .. in the filename anywhere so you can't write outside of the root directory
		for (j=1; j < fileList[i].filename.GetLength(); j++)
		{
			if (fileList[i].filename[j]=='.' && fileList[i].filename[j-1]=='.')
			{
#ifdef _DEBUG
				RakAssert(0);
#endif
				// Just cancel the write entirely
				return;
			}
		}

		WriteFileWithDirectories(fullPath, fileList[i].data, (unsigned int) fileList[i].dataLengthBytes);
	}
}

void FileList::DeleteFiles(const char *applicationDirectory)
{



	char fullPath[512];
	unsigned i,j;

	for (i=0; i < fileList.Size(); i++)
	{
		// The filename should not have .. in the path - if it does ignore it
		for (j=1; j < fileList[i].filename.GetLength(); j++)
		{
			if (fileList[i].filename[j]=='.' && fileList[i].filename[j-1]=='.')
			{
#ifdef _DEBUG
				RakAssert(0);
#endif
				// Just cancel the deletion entirely
				return;
			}
		}

		strcpy_s(fullPath, applicationDirectory);
		FixEndingSlash(fullPath, 512);
		strcat_s(fullPath, fileList[i].filename.C_String());
	
		// Do not rename to _unlink as linux uses unlink
#if defined(_WIN32)
		int result = _unlink(fullPath);
#else
        int result = unlink(fullPath);
#endif
		if (result!=0)
		{
			RAKNET_DEBUG_PRINTF("FileList::DeleteFiles: unlink (%s) failed.\n", fullPath);
		}
	}

}

void FileList::AddCallback(FileListProgress *cb)
{
	if (cb==0)
		return;

	if ((unsigned int) fileListProgressCallbacks.GetIndexOf(cb)==(unsigned int)-1)
		fileListProgressCallbacks.Push(cb, _FILE_AND_LINE_);
}
void FileList::RemoveCallback(FileListProgress *cb)
{
	unsigned int idx = fileListProgressCallbacks.GetIndexOf(cb);
	if (idx!=(unsigned int) -1)
		fileListProgressCallbacks.RemoveAtIndex(idx);
}
void FileList::ClearCallbacks(void)
{
	fileListProgressCallbacks.Clear(true, _FILE_AND_LINE_);
}
void FileList::GetCallbacks(DataStructures::List<FileListProgress*> &callbacks)
{
	callbacks = fileListProgressCallbacks;
}

bool FileList::FixEndingSlash(char *str)
{
#ifdef _WIN32
	if (str[strlen(str) - 1] != '/' && str[strlen(str) - 1] != '\\')
	{
#pragma warning(push)
#pragma warning(disable:4996)
		strcat(str, "\\"); // Only \ works with system commands, used by AutopatcherClient
#pragma warning(pop)
		return true;
	}
#else
	if (str[strlen(str) - 1] != '\\' && str[strlen(str) - 1] != '/')
	{
		strcat(str, "/"); // Only / works with Linux
		return true;
	}
#endif

	return false;
}

bool FileList::FixEndingSlash(char *str, size_t strLength)
{
#ifdef _WIN32
	if (str[strlen(str)-1]!='/' && str[strlen(str)-1]!='\\')
	{
		strcat_s(str, strLength, "\\"); // Only \ works with system commands, used by AutopatcherClient
		return true;
	}
#else
	if (str[strlen(str)-1]!='\\' && str[strlen(str)-1]!='/')
	{
		strcat_s(str, strLength, "/"); // Only / works with Linux
		return true;
	}
#endif

	return false;
}

#endif // _RAKNET_SUPPORT_FileOperations
