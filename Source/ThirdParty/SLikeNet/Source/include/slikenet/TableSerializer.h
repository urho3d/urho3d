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

#ifndef __TABLE_SERIALIZER_H
#define __TABLE_SERIALIZER_H

#include "memoryoverride.h"
#include "DS_Table.h"
#include "Export.h"

namespace SLNet
{
	class BitStream;
}

namespace SLNet
{

class RAK_DLL_EXPORT TableSerializer
{
public:
	static void SerializeTable(DataStructures::Table *in, SLNet::BitStream *out);
	static bool DeserializeTable(unsigned char *serializedTable, unsigned int dataLength, DataStructures::Table *out);
	static bool DeserializeTable(SLNet::BitStream *in, DataStructures::Table *out);
	static void SerializeColumns(DataStructures::Table *in, SLNet::BitStream *out);
	static void SerializeColumns(DataStructures::Table *in, SLNet::BitStream *out, DataStructures::List<int> &skipColumnIndices);
	static bool DeserializeColumns(SLNet::BitStream *in, DataStructures::Table *out);
	static void SerializeRow(DataStructures::Table::Row *in, unsigned keyIn, const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns, SLNet::BitStream *out);
	static void SerializeRow(DataStructures::Table::Row *in, unsigned keyIn, const DataStructures::List<DataStructures::Table::ColumnDescriptor> &columns, SLNet::BitStream *out, DataStructures::List<int> &skipColumnIndices);
	static bool DeserializeRow(SLNet::BitStream *in, DataStructures::Table *out);
	static void SerializeCell(SLNet::BitStream *out, DataStructures::Table::Cell *cell, DataStructures::Table::ColumnType columnType);
	static bool DeserializeCell(SLNet::BitStream *in, DataStructures::Table::Cell *cell, DataStructures::Table::ColumnType columnType);
	static void SerializeFilterQuery(SLNet::BitStream *in, DataStructures::Table::FilterQuery *query);
	// Note that this allocates query->cell->c!
	static bool DeserializeFilterQuery(SLNet::BitStream *out, DataStructures::Table::FilterQuery *query);
	static void SerializeFilterQueryList(SLNet::BitStream *in, DataStructures::Table::FilterQuery *query, unsigned int numQueries, unsigned int maxQueries);
	// Note that this allocates queries, cells, and query->cell->c!. Use DeallocateQueryList to free.
	static bool DeserializeFilterQueryList(SLNet::BitStream *out, DataStructures::Table::FilterQuery **query, unsigned int *numQueries, unsigned int maxQueries, int allocateExtraQueries=0);
	static void DeallocateQueryList(DataStructures::Table::FilterQuery *query, unsigned int numQueries);
};

} // namespace SLNet

#endif

// Test code for the table
/*
#include "LightweightDatabaseServer.h"
#include "LightweightDatabaseClient.h"
#include "TableSerializer.h"
#include "BitStream.h"
#include "StringCompressor.h"
#include "DS_Table.h"
void main(void)
{
	DataStructures::Table table;
	DataStructures::Table::Row *row;
	unsigned int dummydata=12345;

	// Add columns Name (string), IP (binary), score (int), and players (int).
	table.AddColumn("Name", DataStructures::Table::STRING);
	table.AddColumn("IP", DataStructures::Table::BINARY);
	table.AddColumn("Score", DataStructures::Table::NUMERIC);
	table.AddColumn("Players", DataStructures::Table::NUMERIC);
	table.AddColumn("Empty Test Column", DataStructures::Table::STRING);
	RakAssert(table.GetColumnCount()==5);
	row=table.AddRow(0);
	RakAssert(row);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	row->UpdateCell(2,5);
	row->UpdateCell(3,10);
	//row->UpdateCell(4,"should be unique");

	row=table.AddRow(1);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	row->UpdateCell(2,5);
	row->UpdateCell(3,15);

	row=table.AddRow(2);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	row->UpdateCell(2,5);
	row->UpdateCell(3,20);

	row=table.AddRow(3);
	RakAssert(row);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	row->UpdateCell(2,15);
	row->UpdateCell(3,5);
	row->UpdateCell(4,"col index 4");

	row=table.AddRow(4);
	RakAssert(row);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	//row->UpdateCell(2,25);
	row->UpdateCell(3,30);
	//row->UpdateCell(4,"should be unique");

	row=table.AddRow(5);
	RakAssert(row);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	//row->UpdateCell(2,25);
	row->UpdateCell(3,5);
	//row->UpdateCell(4,"should be unique");

	row=table.AddRow(6);
	RakAssert(row);
	row->UpdateCell(0,"Kevin Jenkins");
	row->UpdateCell(1,sizeof(dummydata), (char*)&dummydata);
	row->UpdateCell(2,35);
	//row->UpdateCell(3,40);
	//row->UpdateCell(4,"should be unique");

	row=table.AddRow(7);
	RakAssert(row);
	row->UpdateCell(0,"Bob Jenkins");

	row=table.AddRow(8);
	RakAssert(row);
	row->UpdateCell(0,"Zack Jenkins");

	// Test multi-column sorting
	DataStructures::Table::Row *rows[30];
	DataStructures::Table::SortQuery queries[4];
	queries[0].columnIndex=0;
	queries[0].operation=DataStructures::Table::QS_INCREASING_ORDER;
	queries[1].columnIndex=1;
	queries[1].operation=DataStructures::Table::QS_INCREASING_ORDER;
	queries[2].columnIndex=2;
	queries[2].operation=DataStructures::Table::QS_INCREASING_ORDER;
	queries[3].columnIndex=3;
	queries[3].operation=DataStructures::Table::QS_DECREASING_ORDER;
	table.SortTable(queries, 4, rows);
	unsigned i;
	char out[256];
	RAKNET_DEBUG_PRINTF("Sort: Ascending except for column index 3\n");
	for (i=0; i < table.GetRowCount(); i++)
	{
		table.PrintRow(out,256,',',true, rows[i]);
		RAKNET_DEBUG_PRINTF("%s\n", out);
	}

	// Test query:
	// Don't return column 3, and swap columns 0 and 2
	unsigned columnsToReturn[4];
	columnsToReturn[0]=2;
	columnsToReturn[1]=1;
	columnsToReturn[2]=0;
	columnsToReturn[3]=4;
	DataStructures::Table resultsTable;
	table.QueryTable(columnsToReturn,4,0,0,&resultsTable);
	RAKNET_DEBUG_PRINTF("Query: Don't return column 3, and swap columns 0 and 2:\n");
	for (i=0; i < resultsTable.GetRowCount(); i++)
	{
		resultsTable.PrintRow(out,256,',',true, resultsTable.GetRowByIndex(i));
		RAKNET_DEBUG_PRINTF("%s\n", out);
	}

	// Test filter:
	// Only return rows with column index 4 empty
	DataStructures::Table::FilterQuery inclusionFilters[3];
	inclusionFilters[0].columnIndex=4;
	inclusionFilters[0].operation=DataStructures::Table::QF_IS_EMPTY;
	// inclusionFilters[0].cellValue; // Unused for IS_EMPTY
	table.QueryTable(0,0,inclusionFilters,1,&resultsTable);
	RAKNET_DEBUG_PRINTF("Filter: Only return rows with column index 4 empty:\n");
	for (i=0; i < resultsTable.GetRowCount(); i++)
	{
		resultsTable.PrintRow(out,256,',',true, resultsTable.GetRowByIndex(i));
		RAKNET_DEBUG_PRINTF("%s\n", out);
	}

	// Column 5 empty and column 0 == Kevin Jenkins
	inclusionFilters[0].columnIndex=4;
	inclusionFilters[0].operation=DataStructures::Table::QF_IS_EMPTY;
	inclusionFilters[1].columnIndex=0;
	inclusionFilters[1].operation=DataStructures::Table::QF_EQUAL;
	inclusionFilters[1].cellValue.Set("Kevin Jenkins");
	table.QueryTable(0,0,inclusionFilters,2,&resultsTable);
	RAKNET_DEBUG_PRINTF("Filter: Column 5 empty and column 0 == Kevin Jenkins:\n");
	for (i=0; i < resultsTable.GetRowCount(); i++)
	{
		resultsTable.PrintRow(out,256,',',true, resultsTable.GetRowByIndex(i));
		RAKNET_DEBUG_PRINTF("%s\n", out);
	}

	SLNet::BitStream bs;
	RAKNET_DEBUG_PRINTF("PreSerialize:\n");
	for (i=0; i < table.GetRowCount(); i++)
	{
		table.PrintRow(out,256,',',true, table.GetRowByIndex(i));
		RAKNET_DEBUG_PRINTF("%s\n", out);
	}
	StringCompressor::AddReference();
	TableSerializer::Serialize(&table, &bs);
	TableSerializer::Deserialize(&bs, &table);
	StringCompressor::RemoveReference();
	RAKNET_DEBUG_PRINTF("PostDeserialize:\n");
	for (i=0; i < table.GetRowCount(); i++)
	{
		table.PrintRow(out,256,',',true, table.GetRowByIndex(i));
		RAKNET_DEBUG_PRINTF("%s\n", out);
	}
	int a=5;
}
*/
