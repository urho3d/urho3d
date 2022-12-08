/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#include "slikenet/TableSerializer.h"
#include "slikenet/DS_Table.h"
#include "slikenet/BitStream.h"
#include "slikenet/StringCompressor.h"
#include "slikenet/assert.h"

using namespace SLNet;

void TableSerializer::SerializeTable(DataStructures::Table *in, SLNet::BitStream *out)
{
	DataStructures::Page<unsigned, DataStructures::Table::Row*, _TABLE_BPLUS_TREE_ORDER> *cur = in->GetRows().GetListHead();
	const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns=in->GetColumns();
	SerializeColumns(in, out);
	out->Write((unsigned)in->GetRows().Size());
	unsigned rowIndex;
	while (cur)
	{
		for (rowIndex=0; rowIndex < (unsigned)cur->size; rowIndex++)
		{
			SerializeRow(cur->data[rowIndex], cur->keys[rowIndex], columns, out);
		}
		cur=cur->next;
	}
}
void TableSerializer::SerializeColumns(DataStructures::Table *in, SLNet::BitStream *out)
{
	const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns=in->GetColumns();
	out->Write((unsigned)columns.Size());
	unsigned i;
	for (i=0; i<columns.Size(); i++)
	{
		StringCompressor::Instance()->EncodeString(columns[i].columnName, _TABLE_MAX_COLUMN_NAME_LENGTH, out);
		out->Write((unsigned char)columns[i].columnType);
	}
}
void TableSerializer::SerializeColumns(DataStructures::Table *in, SLNet::BitStream *out, DataStructures::List<int> &skipColumnIndices)
{
	const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns=in->GetColumns();
	out->Write((unsigned)columns.Size()-skipColumnIndices.Size());
	unsigned i;
	for (i=0; i<columns.Size(); i++)
	{
		if (skipColumnIndices.GetIndexOf(i)==(unsigned)-1)
		{
			StringCompressor::Instance()->EncodeString(columns[i].columnName, _TABLE_MAX_COLUMN_NAME_LENGTH, out);
			out->Write((unsigned char)columns[i].columnType);
		}		
	}
}
bool TableSerializer::DeserializeTable(unsigned char *serializedTable, unsigned int dataLength, DataStructures::Table *out)
{
	SLNet::BitStream in((unsigned char*) serializedTable, dataLength, false);
	return DeserializeTable(&in, out);
}
bool TableSerializer::DeserializeTable(SLNet::BitStream *in, DataStructures::Table *out)
{
	unsigned rowSize;
	DeserializeColumns(in,out);
	if (in->Read(rowSize)==false || rowSize>100000)
	{
		RakAssert(0);
		return false; // Hacker crash prevention
	}

	unsigned rowIndex;
	for (rowIndex=0; rowIndex < rowSize; rowIndex++)
	{
		if (DeserializeRow(in, out)==false)
			return false;
	}
	return true;
}
bool TableSerializer::DeserializeColumns(SLNet::BitStream *in, DataStructures::Table *out)
{
	unsigned columnSize;
	unsigned char columnType;
	char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH];
	if (in->Read(columnSize)==false || columnSize > 10000)
		return false; // Hacker crash prevention

	out->Clear();
	unsigned i;
	for (i=0; i<columnSize; i++)
	{
		StringCompressor::Instance()->DecodeString(columnName, 32, in);
		in->Read(columnType);
		out->AddColumn(columnName, (DataStructures::Table::ColumnType)columnType);
	}
	return true;
}
void TableSerializer::SerializeRow(DataStructures::Table::Row *in, unsigned keyIn, const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns, SLNet::BitStream *out)
{
	unsigned cellIndex;
	out->Write(keyIn);
	unsigned int columnsSize = columns.Size();
	out->Write(columnsSize);
	for (cellIndex=0; cellIndex<columns.Size(); cellIndex++)
	{
		out->Write(cellIndex);
		SerializeCell(out, in->cells[cellIndex], columns[cellIndex].columnType);
	}
}
void TableSerializer::SerializeRow(DataStructures::Table::Row *in, unsigned keyIn, const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns, SLNet::BitStream *out, DataStructures::List<int> &skipColumnIndices)
{
	unsigned cellIndex;
	out->Write(keyIn);
	unsigned int numEntries=0;
	for (cellIndex=0; cellIndex<columns.Size(); cellIndex++)
	{
		if (skipColumnIndices.GetIndexOf(cellIndex)==(unsigned)-1)
		{
			numEntries++;
		}
	}
	out->Write(numEntries);

	for (cellIndex=0; cellIndex<columns.Size(); cellIndex++)
	{
		if (skipColumnIndices.GetIndexOf(cellIndex)==(unsigned)-1)
		{
			out->Write(cellIndex);
			SerializeCell(out, in->cells[cellIndex], columns[cellIndex].columnType);
		}
	}
}
bool TableSerializer::DeserializeRow(SLNet::BitStream *in, DataStructures::Table *out)
{
	const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns=out->GetColumns();
	unsigned numEntries;
	DataStructures::Table::Row *row;
	unsigned key;
	if (in->Read(key)==false)
		return false;
	row=out->AddRow(key);
	unsigned int cnt;
	in->Read(numEntries);
	for (cnt=0; cnt<numEntries; cnt++)
	{
		unsigned cellIndex;
		in->Read(cellIndex);
		if (DeserializeCell(in, row->cells[cellIndex], columns[cellIndex].columnType)==false)
		{
			out->RemoveRow(key);
			return false;
		}
	}
	return true;
}
void TableSerializer::SerializeCell(SLNet::BitStream *out, DataStructures::Table::Cell *cell, DataStructures::Table::ColumnType columnType)
{
	out->Write(cell->isEmpty);
	if (cell->isEmpty==false)
	{
		if (columnType==DataStructures::Table::NUMERIC)
		{
			out->Write(cell->i);
		}
		else if (columnType==DataStructures::Table::STRING)
		{
			StringCompressor::Instance()->EncodeString(cell->c, 65535, out);
		}
		else if (columnType==DataStructures::Table::POINTER)
		{
			out->Write(cell->ptr);
		}
		else
		{
			// Binary
			RakAssert(columnType==DataStructures::Table::BINARY);
			RakAssert(cell->i>0);
			unsigned binaryLength;
			binaryLength=(unsigned)cell->i;
			out->Write(binaryLength);
			out->WriteAlignedBytes((const unsigned char*) cell->c, (const unsigned int) cell->i);
		}
	}
}
bool TableSerializer::DeserializeCell(SLNet::BitStream *in, DataStructures::Table::Cell *cell, DataStructures::Table::ColumnType columnType)
{
	bool isEmpty=false;
	double value;
	void *ptr;
	char tempString[65535];
	cell->Clear();

	if (in->Read(isEmpty)==false)
		return false;
	if (isEmpty==false)
	{
		if (columnType==DataStructures::Table::NUMERIC)
		{
			if (in->Read(value)==false)
				return false;
			cell->Set(value);
		}
		else if (columnType==DataStructures::Table::STRING)
		{
			if (StringCompressor::Instance()->DecodeString(tempString, 65535, in)==false)
				return false;
			cell->Set(tempString);
		}
		else if (columnType==DataStructures::Table::POINTER)
		{
			if (in->Read(ptr)==false)
				return false;
			cell->SetPtr(ptr);
		}
		else
		{
			unsigned binaryLength;
			// Binary
			RakAssert(columnType==DataStructures::Table::BINARY);
			if (in->Read(binaryLength)==false || binaryLength > 10000000)
				return false; // Sanity check to max binary cell of 10 megabytes
			in->AlignReadToByteBoundary();
			if (BITS_TO_BYTES(in->GetNumberOfUnreadBits())<(BitSize_t)binaryLength)
				return false;
			cell->Set((char*) in->GetData()+BITS_TO_BYTES(in->GetReadOffset()), (int) binaryLength);
			in->IgnoreBits(BYTES_TO_BITS((int) binaryLength));
		}
	}
	return true;
}
void TableSerializer::SerializeFilterQuery(SLNet::BitStream *in, DataStructures::Table::FilterQuery *query)
{
	StringCompressor::Instance()->EncodeString(query->columnName,_TABLE_MAX_COLUMN_NAME_LENGTH,in,0);
	in->WriteCompressed(query->columnIndex);
	in->Write((unsigned char) query->operation);
	in->Write(query->cellValue->isEmpty);
	if (query->cellValue->isEmpty==false)
	{
		in->Write(query->cellValue->i);
		in->WriteAlignedBytesSafe((const char*)query->cellValue->c,(const unsigned int)query->cellValue->i,10000000); // Sanity check to max binary cell of 10 megabytes
		in->Write(query->cellValue->ptr);

	}
}
bool TableSerializer::DeserializeFilterQuery(SLNet::BitStream *out, DataStructures::Table::FilterQuery *query)
{
	bool b;
	RakAssert(query->cellValue);
	StringCompressor::Instance()->DecodeString(query->columnName,_TABLE_MAX_COLUMN_NAME_LENGTH,out,0);
	out->ReadCompressed(query->columnIndex);
	unsigned char op;
	out->Read(op);
	query->operation=(DataStructures::Table::FilterQueryType) op;
	query->cellValue->Clear();
	b=out->Read(query->cellValue->isEmpty);
	if (query->cellValue->isEmpty==false)
	{
		// HACK - cellValue->i is used for integer, character, and binary data. However, for character and binary c will be 0. So use that to determine if the data was integer or not.
		out->Read(query->cellValue->i);
		unsigned int inputLength;
		out->ReadAlignedBytesSafeAlloc(&query->cellValue->c,inputLength,10000000); // Sanity check to max binary cell of 10 megabytes
		if (query->cellValue->c)
			query->cellValue->i=inputLength;
		b=out->Read(query->cellValue->ptr);
	}
	return b;
}
void TableSerializer::SerializeFilterQueryList(SLNet::BitStream *in, DataStructures::Table::FilterQuery *query, unsigned int numQueries, unsigned int maxQueries)
{
	(void) maxQueries;
	in->Write((bool)(query && numQueries>0));
	if (query==0 || numQueries<=0)
		return;

	RakAssert(numQueries<=maxQueries);
	in->WriteCompressed(numQueries);
	unsigned i;
	for (i=0; i < numQueries; i++)
	{
		SerializeFilterQuery(in, query);
	}
}
bool TableSerializer::DeserializeFilterQueryList(SLNet::BitStream *out, DataStructures::Table::FilterQuery **query, unsigned int *numQueries, unsigned int maxQueries, int allocateExtraQueries)
{
	bool b, anyQueries=false;
	out->Read(anyQueries);
	if (anyQueries==false)
	{
		if (allocateExtraQueries<=0)
			*query=0;
		else
			*query=new DataStructures::Table::FilterQuery[allocateExtraQueries];

		*numQueries=0;
		return true;
	}
	b=out->ReadCompressed(*numQueries);
	if (*numQueries>maxQueries)
	{
		RakAssert(0);
		*numQueries=maxQueries;
	}
	if (*numQueries==0)
		return b;

	*query=new DataStructures::Table::FilterQuery[*numQueries+allocateExtraQueries];
	DataStructures::Table::FilterQuery *queryPtr = *query;

	unsigned i;
	for (i=0; i < *numQueries; i++)
	{
		queryPtr[i].cellValue=new DataStructures::Table::Cell;
		b=DeserializeFilterQuery(out, queryPtr+i);
	}

	return b;
}
void TableSerializer::DeallocateQueryList(DataStructures::Table::FilterQuery *query, unsigned int numQueries)
{
	if (query==0 || numQueries==0)
		return;

	unsigned i;
	for (i=0; i < numQueries; i++)
		SLNet::OP_DELETE(query[i].cellValue, _FILE_AND_LINE_);
	SLNet::OP_DELETE_ARRAY(query, _FILE_AND_LINE_);
}
