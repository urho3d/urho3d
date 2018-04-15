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

#include "slikenet/DS_Table.h"
#include "slikenet/DS_OrderedList.h"
#include <string.h>
#include "slikenet/assert.h"
#include "slikenet/assert.h"
#include "slikenet/Itoa.h"
#include "slikenet/linux_adapter.h"
#include "slikenet/osx_adapter.h"

using namespace DataStructures;

void ExtendRows(Table::Row* input, int index)
{
	(void) index;
	input->cells.Insert(SLNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_), _FILE_AND_LINE_ );
}
void FreeRow(Table::Row* input, int index)
{
	(void) index;

	unsigned i;
	for (i=0; i < input->cells.Size(); i++)
	{
		SLNet::OP_DELETE(input->cells[i], _FILE_AND_LINE_);
	}
	SLNet::OP_DELETE(input, _FILE_AND_LINE_);
}
Table::Cell::Cell()
{
	isEmpty=true;
	c=0;
	ptr=0;
	i=0.0;
}
Table::Cell::~Cell()
{
	Clear();
}
Table::Cell& Table::Cell::operator = ( const Table::Cell& input )
{
	isEmpty=input.isEmpty;
	i=input.i;
	ptr=input.ptr;
	if (c)
		rakFree_Ex(c, _FILE_AND_LINE_);
	if (input.c)
	{
		c = (char*) rakMalloc_Ex( (int) i, _FILE_AND_LINE_ );
		memcpy(c, input.c, (int) i);
	}
	else
		c=0;
	return *this;
}
Table::Cell::Cell( const Table::Cell & input)
{
	isEmpty=input.isEmpty;
	i=input.i;
	ptr=input.ptr;
	if (input.c)
	{
		if (c)
			rakFree_Ex(c, _FILE_AND_LINE_);
		c =  (char*) rakMalloc_Ex( (int) i, _FILE_AND_LINE_ );
		memcpy(c, input.c, (int) i);
	}
}
void Table::Cell::Set(double input)
{
	Clear();
	i=input;
	c=0;
	ptr=0;
	isEmpty=false;
}
void Table::Cell::Set(unsigned int input)
{
	Set((int) input);
}
void Table::Cell::Set(int input)
{
	Clear();
	i=(double) input;
	c=0;
	ptr=0;
	isEmpty=false;
}

void Table::Cell::Set(const char *input)
{
	Clear();
		
	if (input)
	{
		i=(int)strlen(input)+1;
		c =  (char*) rakMalloc_Ex( (int) i, _FILE_AND_LINE_ );
		strcpy_s(c, (int) i, input);
	}
	else
	{
		c=0;
		i=0;
	}
	ptr=0;
	isEmpty=false;
}
void Table::Cell::Set(const char *input, int inputLength)
{
	Clear();
	if (input)
	{
		c = (char*) rakMalloc_Ex( inputLength, _FILE_AND_LINE_ );
		i=inputLength;
		memcpy(c, input, inputLength);
	}
	else
	{
		c=0;
		i=0;
	}
	ptr=0;
	isEmpty=false;
}
void Table::Cell::SetPtr(void* p)
{
	Clear();
	c=0;
	ptr=p;
	isEmpty=false;
}
void Table::Cell::Get(int *output)
{
	RakAssert(isEmpty==false);
	int o = (int) i;
	*output=o;
}
void Table::Cell::Get(double *output)
{
	RakAssert(isEmpty==false);
	*output=i;
}
void Table::Cell::Get(char *output)
{
	RakAssert(isEmpty == false);
#pragma warning(push)
#pragma warning(disable:4996)
	strcpy(output, c);
#pragma warning(pop)
}
void Table::Cell::Get(char *output, size_t outputLength)
{
	RakAssert(isEmpty==false);
	strcpy_s(output, outputLength, c);
}
void Table::Cell::Get(char *output, int *outputLength)
{
	RakAssert(isEmpty==false);
	memcpy(output, c, (int) i);
	if (outputLength)
		*outputLength=(int) i;
}
SLNet::RakString Table::Cell::ToString(ColumnType columnType)
{
	if (isEmpty)
		return SLNet::RakString();

	if (columnType==NUMERIC)
	{
		return SLNet::RakString("%f", i);
	}
	else if (columnType==STRING)
	{
		return SLNet::RakString(c);
	}
	else if (columnType==BINARY)
	{
		return SLNet::RakString("<Binary>");
	}
	else if (columnType==POINTER)
	{
		return SLNet::RakString("%p", ptr);
	}

	return SLNet::RakString();
}
Table::Cell::Cell(double numericValue, char *charValue, void *ptr, ColumnType type)
{
	SetByType(numericValue,charValue,ptr,type);
}
void Table::Cell::SetByType(double numericValue, char *charValue, void *inPtr, ColumnType type)
{
	isEmpty=true;
	if (type==NUMERIC)
	{
		Set(numericValue);
	}
	else if (type==STRING)
	{
		Set(charValue);
	}
	else if (type==BINARY)
	{
		Set(charValue, (int) numericValue);
	}
	else if (type==POINTER)
	{
		SetPtr(inPtr);
	}
	else
	{
		inPtr=(void*) charValue;
	}
}
Table::ColumnType Table::Cell::EstimateColumnType(void) const
{
	if (c)
	{
		if (i!=0.0f)
			return BINARY;
		else
			return STRING;
	}

	if (ptr)
		return POINTER;
	return NUMERIC;
}
void Table::Cell::Clear(void)
{
	if (isEmpty==false && c)
	{
		rakFree_Ex(c, _FILE_AND_LINE_);
		c=0;
	}
	isEmpty=true;
}
Table::ColumnDescriptor::ColumnDescriptor()
{

}
Table::ColumnDescriptor::~ColumnDescriptor()
{

}
Table::ColumnDescriptor::ColumnDescriptor(const char cn[_TABLE_MAX_COLUMN_NAME_LENGTH], ColumnType ct)
{
	columnType=ct;
	strcpy_s(columnName, cn);
}
void Table::Row::UpdateCell(unsigned columnIndex, double value)
{
	cells[columnIndex]->Clear();
	cells[columnIndex]->Set(value);

//	cells[columnIndex]->i=value;
//	cells[columnIndex]->c=0;
//	cells[columnIndex]->isEmpty=false;
}
void Table::Row::UpdateCell(unsigned columnIndex, const char *str)
{
	cells[columnIndex]->Clear();
	cells[columnIndex]->Set(str);
}
void Table::Row::UpdateCell(unsigned columnIndex, int byteLength, const char *data)
{
	cells[columnIndex]->Clear();
	cells[columnIndex]->Set(data,byteLength);
}
Table::Table()
{
}
Table::~Table()
{
	Clear();
}
unsigned Table::AddColumn(const char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH], ColumnType columnType)
{
	if (columnName[0]==0)
		return (unsigned) -1;

	// Add this column.
	columns.Insert(Table::ColumnDescriptor(columnName, columnType), _FILE_AND_LINE_);

	// Extend the rows by one
	rows.ForEachData(ExtendRows);

	return columns.Size()-1;
}
void Table::RemoveColumn(unsigned columnIndex)
{
	if (columnIndex >= columns.Size())
		return;

	columns.RemoveAtIndex(columnIndex);

	// Remove this index from each row.
	int i;
	DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
	while (cur)
	{
		for (i=0; i < cur->size; i++)
		{
			SLNet::OP_DELETE(cur->data[i]->cells[columnIndex], _FILE_AND_LINE_);
			cur->data[i]->cells.RemoveAtIndex(columnIndex);
		}

		cur=cur->next;
	}
}
unsigned Table::ColumnIndex(const char *columnName) const
{
	unsigned columnIndex;
	for (columnIndex=0; columnIndex<columns.Size(); columnIndex++)
		if (strcmp(columnName, columns[columnIndex].columnName)==0)
			return columnIndex;
	return (unsigned)-1;
}
unsigned Table::ColumnIndex(char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH]) const
{
	return ColumnIndex((const char *) columnName);
}
char* Table::ColumnName(unsigned index) const
{
	if (index >= columns.Size())
		return 0;
	else
		return (char*)columns[index].columnName;
}
Table::ColumnType Table::GetColumnType(unsigned index) const
{
	if (index >= columns.Size())
		return (Table::ColumnType) 0;
	else
		return columns[index].columnType;
}
unsigned Table::GetColumnCount(void) const
{
	return columns.Size();
}
unsigned Table::GetRowCount(void) const
{
	return rows.Size();
}
Table::Row* Table::AddRow(unsigned rowId)
{
	Row *newRow;
	newRow = SLNet::OP_NEW<Row>( _FILE_AND_LINE_ );
	if (rows.Insert(rowId, newRow)==false)
	{
		SLNet::OP_DELETE(newRow, _FILE_AND_LINE_);
		return 0; // Already exists
	}
	unsigned rowIndex;
	for (rowIndex=0; rowIndex < columns.Size(); rowIndex++)
		newRow->cells.Insert(SLNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_), _FILE_AND_LINE_ );
	return newRow;
}
Table::Row* Table::AddRow(unsigned rowId, DataStructures::List<Cell> &initialCellValues)
{
	Row *newRow = SLNet::OP_NEW<Row>( _FILE_AND_LINE_ );
	unsigned rowIndex;
	for (rowIndex=0; rowIndex < columns.Size(); rowIndex++)
	{
		if (rowIndex < initialCellValues.Size() && initialCellValues[rowIndex].isEmpty==false)
		{
			Table::Cell *c;
			c = SLNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_);
			c->SetByType(initialCellValues[rowIndex].i,initialCellValues[rowIndex].c,initialCellValues[rowIndex].ptr,columns[rowIndex].columnType);
			newRow->cells.Insert(c, _FILE_AND_LINE_ );
		}
		else
			newRow->cells.Insert(SLNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_), _FILE_AND_LINE_ );
	}
	rows.Insert(rowId, newRow);
	return newRow;
}
Table::Row* Table::AddRow(unsigned rowId, DataStructures::List<Cell*> &initialCellValues, bool copyCells)
{
	Row *newRow = SLNet::OP_NEW<Row>( _FILE_AND_LINE_ );
	unsigned rowIndex;
	for (rowIndex=0; rowIndex < columns.Size(); rowIndex++)
	{
		if (rowIndex < initialCellValues.Size() && initialCellValues[rowIndex] && initialCellValues[rowIndex]->isEmpty==false)
		{
			if (copyCells==false)
				newRow->cells.Insert(SLNet::OP_NEW_4<Table::Cell>( _FILE_AND_LINE_, initialCellValues[rowIndex]->i, initialCellValues[rowIndex]->c, initialCellValues[rowIndex]->ptr, columns[rowIndex].columnType), _FILE_AND_LINE_);
			else
			{
				Table::Cell *c = SLNet::OP_NEW<Table::Cell>( _FILE_AND_LINE_ );
				newRow->cells.Insert(c, _FILE_AND_LINE_);
				*c=*(initialCellValues[rowIndex]);
			}
		}
		else
			newRow->cells.Insert(SLNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_), _FILE_AND_LINE_);
	}
	rows.Insert(rowId, newRow);
	return newRow;
}
Table::Row* Table::AddRowColumns(unsigned rowId, Row *row, DataStructures::List<unsigned> columnIndices)
{
	Row *newRow = SLNet::OP_NEW<Row>( _FILE_AND_LINE_ );
	unsigned columnIndex;
	for (columnIndex=0; columnIndex < columnIndices.Size(); columnIndex++)
	{
		if (row->cells[columnIndices[columnIndex]]->isEmpty==false)
		{
			newRow->cells.Insert(SLNet::OP_NEW_4<Table::Cell>( _FILE_AND_LINE_,
				row->cells[columnIndices[columnIndex]]->i,
				row->cells[columnIndices[columnIndex]]->c,
				row->cells[columnIndices[columnIndex]]->ptr,
				columns[columnIndex].columnType
				), _FILE_AND_LINE_);
		}
		else
		{
			newRow->cells.Insert(SLNet::OP_NEW<Table::Cell>(_FILE_AND_LINE_), _FILE_AND_LINE_);
		}
	}
	rows.Insert(rowId, newRow);
	return newRow;
}
bool Table::RemoveRow(unsigned rowId)
{
	Row *out;
	if (rows.Delete(rowId, out))
	{
		DeleteRow(out);
		return true;
	}
	return false;
}
void Table::RemoveRows(Table *tableContainingRowIDs)
{
	unsigned i;
	DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur = tableContainingRowIDs->GetRows().GetListHead();
	while (cur)
	{
		for (i=0; i < (unsigned)cur->size; i++)
		{
			rows.Delete(cur->keys[i]);
		}
		cur=cur->next;
	}
	return;
}
bool Table::UpdateCell(unsigned rowId, unsigned columnIndex, int value)
{
	RakAssert(columns[columnIndex].columnType==NUMERIC);

	Row *row = GetRowByID(rowId);
	if (row)
	{
		row->UpdateCell(columnIndex, value);
		return true;
	}
	return false;
}
bool Table::UpdateCell(unsigned rowId, unsigned columnIndex, char *str)
{
	RakAssert(columns[columnIndex].columnType==STRING);

	Row *row = GetRowByID(rowId);
	if (row)
	{
		row->UpdateCell(columnIndex, str);
		return true;
	}
	return false;
}
bool Table::UpdateCell(unsigned rowId, unsigned columnIndex, int byteLength, char *data)
{
	RakAssert(columns[columnIndex].columnType==BINARY);

	Row *row = GetRowByID(rowId);
	if (row)
	{
		row->UpdateCell(columnIndex, byteLength, data);
		return true;
	}
	return false;
}
bool Table::UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, int value)
{
	RakAssert(columns[columnIndex].columnType==NUMERIC);

	Row *row = GetRowByIndex(rowIndex,0);
	if (row)
	{
		row->UpdateCell(columnIndex, value);
		return true;
	}
	return false;
}
bool Table::UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, char *str)
{
	RakAssert(columns[columnIndex].columnType==STRING);

	Row *row = GetRowByIndex(rowIndex,0);
	if (row)
	{
		row->UpdateCell(columnIndex, str);
		return true;
	}
	return false;
}
bool Table::UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, int byteLength, char *data)
{
	RakAssert(columns[columnIndex].columnType==BINARY);

	Row *row = GetRowByIndex(rowIndex,0);
	if (row)
	{
		row->UpdateCell(columnIndex, byteLength, data);
		return true;
	}
	return false;
}
void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, int *output)
{
	RakAssert(columns[columnIndex].columnType==NUMERIC);

	Row *row = GetRowByIndex(rowIndex,0);
	if (row)
	{
		row->cells[columnIndex]->Get(output);
	}
}
void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output)
{
	RakAssert(columns[columnIndex].columnType == STRING);

	Row *row = GetRowByIndex(rowIndex, 0);
	if (row)
	{
		row->cells[columnIndex]->Get(output);
	}
}
void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output, size_t outputLength)
{
	RakAssert(columns[columnIndex].columnType==STRING);

	Row *row = GetRowByIndex(rowIndex,0);
	if (row)
	{
		row->cells[columnIndex]->Get(output, outputLength);
	}
}
void Table::GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output, int *outputLength)
{
	RakAssert(columns[columnIndex].columnType==BINARY);

	Row *row = GetRowByIndex(rowIndex,0);
	if (row)
	{
		row->cells[columnIndex]->Get(output, outputLength);
	}
}
Table::FilterQuery::FilterQuery()
{
	columnName[0]=0;
}
Table::FilterQuery::~FilterQuery()
{

}
Table::FilterQuery::FilterQuery(unsigned column, Cell *cell, FilterQueryType op)
{
	columnIndex=column;
	cellValue=cell;
	operation=op;
}
Table::Row* Table::GetRowByID(unsigned rowId) const
{
	Row *row;
	if (rows.Get(rowId, row))
		return row;
	return 0;
}

Table::Row* Table::GetRowByIndex(unsigned rowIndex, unsigned *key) const
{
	DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
	while (cur)
	{
		if (rowIndex < (unsigned)cur->size)
		{
			if (key)
				*key=cur->keys[rowIndex];
			return cur->data[rowIndex];
		}
		if (rowIndex <= (unsigned)cur->size)
			rowIndex-=cur->size;
		else
			return 0;
		cur=cur->next;
	}
	return 0;
}

void Table::QueryTable(unsigned *columnIndicesSubset, unsigned numColumnSubset, FilterQuery *inclusionFilters, unsigned numInclusionFilters, unsigned *rowIds, unsigned numRowIDs, Table *result)
{
	unsigned i;
	DataStructures::List<unsigned> columnIndicesToReturn;

	// Clear the result table.
	result->Clear();

	if (columnIndicesSubset && numColumnSubset>0)
	{
		for (i=0; i < numColumnSubset; i++)
		{
			if (columnIndicesSubset[i]<columns.Size())
				columnIndicesToReturn.Insert(columnIndicesSubset[i], _FILE_AND_LINE_);
		}
	}
	else
	{
		for (i=0; i < columns.Size(); i++)
			columnIndicesToReturn.Insert(i, _FILE_AND_LINE_);
	}

	if (columnIndicesToReturn.Size()==0)
		return; // No valid columns specified

	for (i=0; i < columnIndicesToReturn.Size(); i++)
	{
		result->AddColumn(columns[columnIndicesToReturn[i]].columnName,columns[columnIndicesToReturn[i]].columnType);
	}

	// Get the column indices of the filter queries.
	DataStructures::List<unsigned> inclusionFilterColumnIndices;
	if (inclusionFilters && numInclusionFilters>0)
	{
		for (i=0; i < numInclusionFilters; i++)
		{
			if (inclusionFilters[i].columnName[0])
				inclusionFilters[i].columnIndex=ColumnIndex(inclusionFilters[i].columnName);
			if (inclusionFilters[i].columnIndex<columns.Size())
				inclusionFilterColumnIndices.Insert(inclusionFilters[i].columnIndex, _FILE_AND_LINE_);
			else
				inclusionFilterColumnIndices.Insert((unsigned)-1, _FILE_AND_LINE_);
		}
	}

	if (rowIds==0 || numRowIDs==0)
	{
		// All rows
		DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
		while (cur)
		{
			for (i=0; i < (unsigned)cur->size; i++)
			{
				QueryRow(inclusionFilterColumnIndices, columnIndicesToReturn, cur->keys[i], cur->data[i], inclusionFilters, result);
			}
			cur=cur->next;
		}
	}
	else
	{
		// Specific rows
		Row *row;
		for (i=0; i < numRowIDs; i++)
		{
			if (rows.Get(rowIds[i], row))
			{
				QueryRow(inclusionFilterColumnIndices, columnIndicesToReturn, rowIds[i], row, inclusionFilters, result);
			}
		}
	}
}

void Table::QueryRow(DataStructures::List<unsigned> &inclusionFilterColumnIndices, DataStructures::List<unsigned> &columnIndicesToReturn, unsigned key, Table::Row* row, FilterQuery *inclusionFilters, Table *result)
{
	bool pass=false;
	unsigned columnIndex;
	unsigned j;

	// If no inclusion filters, just add the row
	if (inclusionFilterColumnIndices.Size()==0)
	{
		result->AddRowColumns(key, row, columnIndicesToReturn);
	}
	else
	{
		// Go through all inclusion filters.  Only add this row if all filters pass.
		for (j=0; j<inclusionFilterColumnIndices.Size(); j++)
		{
			columnIndex=inclusionFilterColumnIndices[j];
			if (columnIndex!=(unsigned)-1 && row->cells[columnIndex]->isEmpty==false )
			{
				if (columns[inclusionFilterColumnIndices[j]].columnType==STRING &&
					(row->cells[columnIndex]->c==0 ||
					inclusionFilters[j].cellValue->c==0)	)
					continue;

				switch (inclusionFilters[j].operation)
				{
				case QF_EQUAL:
					switch(columns[inclusionFilterColumnIndices[j]].columnType)
					{
					case NUMERIC:
						pass=row->cells[columnIndex]->i==inclusionFilters[j].cellValue->i;
						break;
					case STRING:
						pass=strcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c)==0;
						break;
					case BINARY:
						pass=row->cells[columnIndex]->i==inclusionFilters[j].cellValue->i &&
							memcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c, (int) row->cells[columnIndex]->i)==0;
						break;
					case POINTER:
						pass=row->cells[columnIndex]->ptr==inclusionFilters[j].cellValue->ptr;
						break;
					}
					break;
				case QF_NOT_EQUAL:
					switch(columns[inclusionFilterColumnIndices[j]].columnType)
					{
					case NUMERIC:
						pass=row->cells[columnIndex]->i!=inclusionFilters[j].cellValue->i;
						break;
					case STRING:
						pass=strcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c)!=0;
						break;
					case BINARY:
						pass=row->cells[columnIndex]->i==inclusionFilters[j].cellValue->i &&
							memcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c, (int) row->cells[columnIndex]->i)==0;
						break;
					case POINTER:
						pass=row->cells[columnIndex]->ptr!=inclusionFilters[j].cellValue->ptr;
						break;
					}
					break;
				case QF_GREATER_THAN:
					switch(columns[inclusionFilterColumnIndices[j]].columnType)
					{
					case NUMERIC:
						pass=row->cells[columnIndex]->i>inclusionFilters[j].cellValue->i;
						break;
					case STRING:
						pass=strcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c)>0;
						break;
					case BINARY:
      					break;
					case POINTER:
						pass=row->cells[columnIndex]->ptr>inclusionFilters[j].cellValue->ptr;
						break;
					}
					break;
				case QF_GREATER_THAN_EQ:
					switch(columns[inclusionFilterColumnIndices[j]].columnType)
					{
					case NUMERIC:
						pass=row->cells[columnIndex]->i>=inclusionFilters[j].cellValue->i;
						break;
					case STRING:
						pass=strcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c)>=0;
						break;
					case BINARY:
						break;
					case POINTER:
						pass=row->cells[columnIndex]->ptr>=inclusionFilters[j].cellValue->ptr;
						break;
					}
					break;
				case QF_LESS_THAN:
					switch(columns[inclusionFilterColumnIndices[j]].columnType)
					{
					case NUMERIC:
						pass=row->cells[columnIndex]->i<inclusionFilters[j].cellValue->i;
						break;
					case STRING:
						pass=strcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c)<0;
						break;
					case BINARY:
					  break;
					case POINTER:
						pass=row->cells[columnIndex]->ptr<inclusionFilters[j].cellValue->ptr;
						break;
					}
					break;
				case QF_LESS_THAN_EQ:
					switch(columns[inclusionFilterColumnIndices[j]].columnType)
					{
					case NUMERIC:
						pass=row->cells[columnIndex]->i<=inclusionFilters[j].cellValue->i;
						break;
					case STRING:
						pass=strcmp(row->cells[columnIndex]->c,inclusionFilters[j].cellValue->c)<=0;
						break;
					case BINARY:
						break;
					case POINTER:
						pass=row->cells[columnIndex]->ptr<=inclusionFilters[j].cellValue->ptr;
						break;
					}
					break;
				case QF_IS_EMPTY:
					pass=false;
					break;
				case QF_NOT_EMPTY:
					pass=true;
					break;
				default:
					pass=false;
					RakAssert(0);
					break;
				}
			}
			else
			{
				if (inclusionFilters[j].operation==QF_IS_EMPTY)
					pass=true;
				else
					pass=false; // No value for this cell
			}

			if (pass==false)
				break;
		}

		if (pass)
		{
			result->AddRowColumns(key, row, columnIndicesToReturn);
		}
	}
}

static Table::SortQuery *_sortQueries;
static unsigned _numSortQueries;
static DataStructures::List<unsigned> *_columnIndices;
static DataStructures::List<Table::ColumnDescriptor> *_columns;
int RowSort(Table::Row* const &first, Table::Row* const &second) // first is the one inserting, second is the one already there.
{
	unsigned i, columnIndex;
	for (i=0; i<_numSortQueries; i++)
	{
		columnIndex=(*_columnIndices)[i];
		if (columnIndex==(unsigned)-1)
			continue;

		if (first->cells[columnIndex]->isEmpty==true && second->cells[columnIndex]->isEmpty==false)
			return 1; // Empty cells always go at the end

		if (first->cells[columnIndex]->isEmpty==false && second->cells[columnIndex]->isEmpty==true)
			return -1; // Empty cells always go at the end

		if (_sortQueries[i].operation==Table::QS_INCREASING_ORDER)
		{
			if ((*_columns)[columnIndex].columnType==Table::NUMERIC)
			{
				if (first->cells[columnIndex]->i>second->cells[columnIndex]->i)
					return 1;
				if (first->cells[columnIndex]->i<second->cells[columnIndex]->i)
					return -1;
			}
			else
			{
				// String
				if (strcmp(first->cells[columnIndex]->c,second->cells[columnIndex]->c)>0)
					return 1;
				if (strcmp(first->cells[columnIndex]->c,second->cells[columnIndex]->c)<0)
					return -1;
			}
		}
		else
		{
			if ((*_columns)[columnIndex].columnType==Table::NUMERIC)
			{
				if (first->cells[columnIndex]->i<second->cells[columnIndex]->i)
					return 1;
				if (first->cells[columnIndex]->i>second->cells[columnIndex]->i)
					return -1;
			}
			else
			{
				// String
				if (strcmp(first->cells[columnIndex]->c,second->cells[columnIndex]->c)<0)
					return 1;
				if (strcmp(first->cells[columnIndex]->c,second->cells[columnIndex]->c)>0)
					return -1;
			}
		}
	}

	return 0;
}
void Table::SortTable(Table::SortQuery *sortQueries, unsigned numSortQueries, Table::Row** out)
{
	unsigned i;
	unsigned outLength;
	DataStructures::List<unsigned> columnIndices;
	_sortQueries=sortQueries;
	_numSortQueries=numSortQueries;
	_columnIndices=&columnIndices;
	_columns=&columns;
	bool anyValid=false;

	for (i=0; i < numSortQueries; i++)
	{
		if (sortQueries[i].columnIndex<columns.Size() && columns[sortQueries[i].columnIndex].columnType!=BINARY)
		{
			columnIndices.Insert(sortQueries[i].columnIndex, _FILE_AND_LINE_);
			anyValid=true;
		}
		else
			columnIndices.Insert((unsigned)-1, _FILE_AND_LINE_); // Means don't check this column
	}

	DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur;
	cur = rows.GetListHead();
	if (anyValid==false)
	{
		outLength=0;
		while (cur)
		{
			for (i=0; i < (unsigned)cur->size; i++)
			{
				out[(outLength)++]=cur->data[i];
			}
			cur=cur->next;
		}
		return;
	}

	// Start adding to ordered list.
	DataStructures::OrderedList<Row*, Row*, RowSort> orderedList;
	while (cur)
	{
		for (i=0; i < (unsigned)cur->size; i++)
		{
			RakAssert(cur->data[i]);
			orderedList.Insert(cur->data[i],cur->data[i], true, _FILE_AND_LINE_);
		}
		cur=cur->next;
	}

	outLength=0;
	for (i=0; i < orderedList.Size(); i++)
		out[(outLength)++]=orderedList[i];
}
void Table::PrintColumnHeaders(char *out, int outLength, char columnDelineator) const
{
	if (outLength<=0)
		return;
	if (outLength==1)
	{
		*out=0;
		return;
	}

	unsigned i;
	out[0]=0;
	int len;
	for (i=0; i < columns.Size(); i++)
	{
		if (i!=0)
		{
			len = (int) strlen(out);
			if (len < outLength-1)
				sprintf(out+len, "%c", columnDelineator);
			else
				return;
		}

		len = (int) strlen(out);
		if (len < outLength-(int) strlen(columns[i].columnName))
			sprintf(out+len, "%s", columns[i].columnName);
		else
			return;
	}
}
void Table::PrintRow(char *out, int outLength, char columnDelineator, bool printDelineatorForBinary, Table::Row* inputRow) const
{
	if (outLength<=0)
		return;
	if (outLength==1)
	{
		*out=0;
		return;
	}

	if (inputRow->cells.Size()!=columns.Size())
	{
		strncpy_s(out, outLength, "Cell width does not match column width.\n", outLength);
		out[outLength-1]=0;
		return;
	}

	char buff[512];
	unsigned i;
	int len;
	out[0]=0;
	for (i=0; i < columns.Size(); i++)
	{
        if (columns[i].columnType==NUMERIC)
		{
			if (inputRow->cells[i]->isEmpty==false)
			{
				sprintf(buff, "%f", inputRow->cells[i]->i);
				len=(int)strlen(buff);
			}
			else
				len=0;
			if (i+1!=columns.Size())
				buff[len++]=columnDelineator;
			buff[len]=0;
		}
		else if (columns[i].columnType==STRING)
		{
			if (inputRow->cells[i]->isEmpty==false && inputRow->cells[i]->c)
			{
				strncpy(buff, inputRow->cells[i]->c, 512-2);
				buff[512-2]=0;
				len=(int)strlen(buff);
			}
			else
				len=0;
			if (i+1!=columns.Size())
				buff[len++]=columnDelineator;
			buff[len]=0;
		}
		else if (columns[i].columnType==POINTER)
		{
			if (inputRow->cells[i]->isEmpty==false && inputRow->cells[i]->ptr)
			{
				sprintf(buff, "%p", inputRow->cells[i]->ptr);
				len=(int)strlen(buff);
			}
			else
				len=0;
			if (i+1!=columns.Size())
				buff[len++]=columnDelineator;
			buff[len]=0;
		}
		else
		{
			if (printDelineatorForBinary)
			{
				if (i+1!=columns.Size())
					buff[0]=columnDelineator;
				buff[1]=0;
			}
			else
				buff[0]=0;

		}

		len=(int)strlen(out);
		if (outLength==len+1)
			break;
		strncpy_s(out+len, outLength-len, buff, outLength-len);
		out[outLength-1]=0;
	}
}

void Table::Clear(void)
{
	rows.ForEachData(FreeRow);
	rows.Clear();
	columns.Clear(true, _FILE_AND_LINE_);
}
const List<Table::ColumnDescriptor>& Table::GetColumns(void) const
{
	return columns;
}
const DataStructures::BPlusTree<unsigned, Table::Row*, _TABLE_BPLUS_TREE_ORDER>& Table::GetRows(void) const
{
	return rows;
}
DataStructures::Page<unsigned, DataStructures::Table::Row*, _TABLE_BPLUS_TREE_ORDER> * Table::GetListHead(void)
{
	return rows.GetListHead();
}
unsigned Table::GetAvailableRowId(void) const
{
	bool setKey=false;
	unsigned key=0;
	int i;
	DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur = rows.GetListHead();
	
	while (cur)
	{
		for (i=0; i < cur->size; i++)
		{
			if (setKey==false)
			{
				key=cur->keys[i]+1;
				setKey=true;
			}
			else
			{
				if (key!=cur->keys[i])
					return key;
				key++;
			}
		}

		cur=cur->next;
	}
	return key;
}
void Table::DeleteRow(Table::Row *row)
{
	unsigned rowIndex;
	for (rowIndex=0; rowIndex < row->cells.Size(); rowIndex++)
	{
		SLNet::OP_DELETE(row->cells[rowIndex], _FILE_AND_LINE_);
	}
	SLNet::OP_DELETE(row, _FILE_AND_LINE_);
}
Table& Table::operator = ( const Table& input )
{
	Clear();

	unsigned int i;
	for (i=0; i < input.GetColumnCount(); i++)
		AddColumn(input.ColumnName(i), input.GetColumnType(i));

	DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> *cur = input.GetRows().GetListHead();
	while (cur)
	{
		for (i=0; i < (unsigned int) cur->size; i++)
		{
			AddRow(cur->keys[i], cur->data[i]->cells, false);
		}

		cur=cur->next;
	}

	return *this;
}
