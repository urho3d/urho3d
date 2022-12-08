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

/// \file DS_Table.h
///


#ifndef __TABLE_H
#define __TABLE_H

#include "DS_List.h"
#include "DS_BPlusTree.h"
#include "memoryoverride.h"
#include "Export.h"
#include "string.h"

#define _TABLE_BPLUS_TREE_ORDER 16
#define _TABLE_MAX_COLUMN_NAME_LENGTH 64

/// The namespace DataStructures was only added to avoid compiler errors for commonly named data structures
/// As these data structures are stand-alone, you can use them outside of RakNet for your own projects if you wish.
namespace DataStructures
{

	/// \brief Holds a set of columns, a set of rows, and rows times columns cells.
	/// \details The table data structure is useful if you want to store a set of structures and perform queries on those structures.<BR>
	/// This is a relatively simple and fast implementation of the types of tables commonly used in databases.<BR>
	/// See TableSerializer to serialize data members of the table.<BR>
	/// See LightweightDatabaseClient and LightweightDatabaseServer to transmit the table over the network.
	class RAK_DLL_EXPORT Table
	{
	public:
			
		enum ColumnType
		{
			// Cell::i used
			NUMERIC,

			// Cell::c used to hold a null terminated string.
			STRING,

			// Cell::c holds data.  Cell::i holds data length of c in bytes.
			BINARY,

			// Cell::c holds data.  Not deallocated. Set manually by assigning ptr.
			POINTER,
		};
		
		
		/// Holds the actual data in the table
		// Note: If this structure is changed the struct in the swig files need to be changed as well
		struct RAK_DLL_EXPORT Cell
		{
			Cell();
			~Cell();
			Cell(double numericValue, char *charValue, void *ptr, ColumnType type);
			void SetByType(double numericValue, char *charValue, void *inPtr, ColumnType type);
			void Clear(void);
			
			/// Numeric
			void Set(int input);
			void Set(unsigned int input);
			void Set(double input);

			/// String
			void Set(const char *input);

			/// Binary
			void Set(const char *input, int inputLength);

			/// Pointer
			void SetPtr(void* p);

			/// Numeric
			void Get(int *output);
			void Get(double *output);

			/// String
			void Get(char *output);
			void Get(char *output, size_t outputLength);

			/// Binary
			void Get(char *output, int *outputLength);

			SLNet::RakString ToString(ColumnType columnType);

			// assignment operator and copy constructor
			Cell& operator = ( const Cell& input );
			Cell( const Cell & input);

			ColumnType EstimateColumnType(void) const;

			bool isEmpty;
			double i;
			char *c;
			void *ptr;
		};

		/// Stores the name and type of the column
		/// \internal
		// Note: If this structure is changed the struct in the swig files need to be changed as well
		struct RAK_DLL_EXPORT ColumnDescriptor
		{
			ColumnDescriptor();
			~ColumnDescriptor();
			ColumnDescriptor(const char cn[_TABLE_MAX_COLUMN_NAME_LENGTH],ColumnType ct);

			char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH];
			ColumnType columnType;
		};

		/// Stores the list of cells for this row, and a special flag used for internal sorting
		// Note: If this structure is changed the struct in the swig files need to be changed as well
		struct RAK_DLL_EXPORT Row
		{
			// list of cells
			DataStructures::List<Cell*> cells;

			/// Numeric
			void UpdateCell(unsigned columnIndex, double value);

			/// String
			void UpdateCell(unsigned columnIndex, const char *str);

			/// Binary
			void UpdateCell(unsigned columnIndex, int byteLength, const char *data);
		};
		
		// Operations to perform for cell comparison
		enum FilterQueryType
		{
			QF_EQUAL,
			QF_NOT_EQUAL,
			QF_GREATER_THAN,
			QF_GREATER_THAN_EQ,
			QF_LESS_THAN,
			QF_LESS_THAN_EQ,
			QF_IS_EMPTY,
			QF_NOT_EMPTY,
		};

		// Compare the cell value for a row at columnName to the cellValue using operation.
		// Note: If this structure is changed the struct in the swig files need to be changed as well
		struct RAK_DLL_EXPORT FilterQuery
		{
			FilterQuery();
			~FilterQuery();
			FilterQuery(unsigned column, Cell *cell, FilterQueryType op);

			// If columnName is specified, columnIndex will be looked up using it.
			char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH];
			unsigned columnIndex;
			Cell *cellValue;
			FilterQueryType operation;
		};

		/// Increasing or decreasing sort order
		enum SortQueryType
		{
			QS_INCREASING_ORDER,
			QS_DECREASING_ORDER,
		};
		
		// Sort on increasing or decreasing order for a particular column
		// Note: If this structure is changed the struct in the swig files need to be changed as well
		struct RAK_DLL_EXPORT SortQuery
		{
			/// The index of the table column we are sorting on
			unsigned columnIndex;

			/// See SortQueryType
			SortQueryType operation;
		};

		// Constructor
		Table();

		// Destructor
		~Table();

		/// \brief Adds a column to the table
		/// \param[in] columnName The name of the column
		/// \param[in] columnType What type of data this column will hold
		/// \return The index of the new column
		unsigned AddColumn(const char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH], ColumnType columnType);

		/// \brief Removes a column by index
		/// \param[in] columnIndex The index of the column to remove
		void RemoveColumn(unsigned columnIndex);

		/// \brief Gets the index of a column by name
		/// \details Column indices are stored in the order they are added.
		/// \param[in] columnName The name of the column
		/// \return The index of the column, or (unsigned)-1 if no such column
		unsigned ColumnIndex(char columnName[_TABLE_MAX_COLUMN_NAME_LENGTH]) const;
		unsigned ColumnIndex(const char *columnName) const;

		/// \brief Gives the string name of the column at a certain index
		/// \param[in] index The index of the column
		/// \return The name of the column, or 0 if an invalid index
		char* ColumnName(unsigned index) const;

		/// \brief Returns the type of a column, referenced by index
		/// \param[in] index The index of the column
		/// \return The type of the column
		ColumnType GetColumnType(unsigned index) const;

		/// Returns the number of columns
		/// \return The number of columns in the table
		unsigned GetColumnCount(void) const;

		/// Returns the number of rows
		/// \return The number of rows in the table
		unsigned GetRowCount(void) const;

		/// \brief Adds a row to the table
		/// \details New rows are added with empty values for all cells.  However, if you specify initialCelLValues you can specify initial values
		/// It's up to you to ensure that the values in the specific cells match the type of data used by that row
		/// rowId can be considered the primary key for the row.  It is much faster to lookup a row by its rowId than by searching keys.
		/// rowId must be unique
		/// Rows are stored in sorted order in the table, using rowId as the sort key
		/// \param[in] rowId The UNIQUE primary key for the row.  This can never be changed.
		/// \param[in] initialCellValues Initial values to give the row (optional)
		/// \return The newly added row
		Table::Row* AddRow(unsigned rowId);
		Table::Row* AddRow(unsigned rowId, DataStructures::List<Cell> &initialCellValues);
		Table::Row* AddRow(unsigned rowId, DataStructures::List<Cell*> &initialCellValues, bool copyCells=false);

		/// \brief Removes a row specified by rowId.
		/// \param[in] rowId The ID of the row
		/// \return true if the row was deleted. False if not.
		bool RemoveRow(unsigned rowId);

		/// \brief Removes all the rows with IDs that the specified table also has.
		/// \param[in] tableContainingRowIDs The IDs of the rows
		void RemoveRows(Table *tableContainingRowIDs);

		/// \brief Updates a particular cell in the table.
		/// \note If you are going to update many cells of a particular row, it is more efficient to call GetRow and perform the operations on the row directly.
		/// \note Row pointers do not change, so you can also write directly to the rows for more efficiency.
        /// \param[in] rowId The ID of the row
		/// \param[in] columnIndex The column of the cell
		/// \param[in] value The data to set
		bool UpdateCell(unsigned rowId, unsigned columnIndex, int value);
		bool UpdateCell(unsigned rowId, unsigned columnIndex, char *str);
		bool UpdateCell(unsigned rowId, unsigned columnIndex, int byteLength, char *data);
		bool UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, int value);
		bool UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, char *str);
		bool UpdateCellByIndex(unsigned rowIndex, unsigned columnIndex, int byteLength, char *data);

		/// \brief Note this is much less efficient to call than GetRow, then working with the cells directly.
		/// Numeric, string, binary
		void GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, int *output);
		void GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output);
		void GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output, size_t outputLength);
		void GetCellValueByIndex(unsigned rowIndex, unsigned columnIndex, char *output, int *outputLength);

		/// \brief Gets a row.  More efficient to do this and access Row::cells than to repeatedly call GetCell.
		/// You can also update cells in rows from this function.
		/// \param[in] rowId The ID of the row
		/// \return The desired row, or 0 if no such row.
		Row* GetRowByID(unsigned rowId) const;

		/// \brief Gets a row at a specific index.
		/// rowIndex should be less than GetRowCount()
		/// \param[in] rowIndex The index of the row
		/// \param[out] key The ID of the row returned
		/// \return The desired row, or 0 if no such row.
		Row* GetRowByIndex(unsigned rowIndex, unsigned *key) const;

		/// \brief Queries the table, optionally returning only a subset of columns and rows.
		/// \param[in] columnSubset An array of column indices.  Only columns in this array are returned.  Pass 0 for all columns
		/// \param[in] numColumnSubset The number of elements in \a columnSubset
		/// \param[in] inclusionFilters An array of FilterQuery.  All filters must pass for the row to be returned.
		/// \param[in] numInclusionFilters The number of elements in \a inclusionFilters
		/// \param[in] rowIds An arrow of row IDs.  Only these rows with these IDs are returned.  Pass 0 for all rows.
		/// \param[in] numRowIDs The number of elements in \a rowIds
		/// \param[out] result The result of the query.  If no rows are returned, the table will only have columns.
		void QueryTable(unsigned *columnIndicesSubset, unsigned numColumnSubset, FilterQuery *inclusionFilters, unsigned numInclusionFilters, unsigned *rowIds, unsigned numRowIDs, Table *result);

		/// \brief Sorts the table by rows
		/// \details You can sort the table in ascending or descending order on one or more columns
		/// Columns have precedence in the order they appear in the \a sortQueries array
		/// If a row cell on column n has the same value as a a different row on column n, then the row will be compared on column n+1
		/// \param[in] sortQueries A list of SortQuery structures, defining the sorts to perform on the table
		/// \param[in] numColumnSubset The number of elements in \a numSortQueries
		/// \param[out] out The address of an array of Rows, which will receive the sorted output.  The array must be long enough to contain all returned rows, up to GetRowCount()
		void SortTable(Table::SortQuery *sortQueries, unsigned numSortQueries, Table::Row** out);

		/// \brief Frees all memory in the table.
		void Clear(void);

		/// \brief Prints out the names of all the columns.
		/// \param[out] out A pointer to an array of bytes which will hold the output.
		/// \param[in] outLength The size of the \a out array
		/// \param[in] columnDelineator What character to print to delineate columns
		void PrintColumnHeaders(char *out, int outLength, char columnDelineator) const;

		/// \brief Writes a text representation of the row to \a out.
		/// \param[out] out A pointer to an array of bytes which will hold the output.
		/// \param[in] outLength The size of the \a out array
		/// \param[in] columnDelineator What character to print to delineate columns
		/// \param[in] printDelineatorForBinary Binary output is not printed.  True to still print the delineator.
		/// \param[in] inputRow The row to print
		void PrintRow(char *out, int outLength, char columnDelineator, bool printDelineatorForBinary, Table::Row* inputRow) const;

		/// \brief Direct access to make things easier.
		const DataStructures::List<ColumnDescriptor>& GetColumns(void) const;

		/// \brief Direct access to make things easier.
		const DataStructures::BPlusTree<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER>& GetRows(void) const;

		/// \brief Get the head of a linked list containing all the row data.
		DataStructures::Page<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> * GetListHead(void);

		/// \brief Get the first free row id.
		/// This could be made more efficient.
		unsigned GetAvailableRowId(void) const;

		Table& operator = ( const Table& input );

	protected:
		Table::Row* AddRowColumns(unsigned rowId, Row *row, DataStructures::List<unsigned> columnIndices);

		void DeleteRow(Row *row);

		void QueryRow(DataStructures::List<unsigned> &inclusionFilterColumnIndices, DataStructures::List<unsigned> &columnIndicesToReturn, unsigned key, Table::Row* row, FilterQuery *inclusionFilters, Table *result);

		// 16 is arbitrary and is the order of the BPlus tree.  Higher orders are better for searching while lower orders are better for
		// Insertions and deletions.
		DataStructures::BPlusTree<unsigned, Row*, _TABLE_BPLUS_TREE_ORDER> rows;

		// Columns in the table.
		DataStructures::List<ColumnDescriptor> columns;
	};
}

#endif
