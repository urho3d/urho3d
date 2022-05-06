// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include "../../Core/Variant.h"

#include <SQLite/sqlite3.h>

namespace Urho3D
{

/// %Database query result.
class URHO3D_API DbResult
{
    friend class DbConnection;

public:
    /// Default constructor constructs an empty result object.
    DbResult() :
        numAffectedRows_(-1)
    {
    }

    /// Return number of columns in the resultset or 0 if there is no resultset.
    unsigned GetNumColumns() const { return columns_.Size(); }

    /// Return number of rows in the resultset or 0 if the number of rows is not available.
    unsigned GetNumRows() const { return rows_.Size(); }

    /// Return number of affected rows by the DML query or -1 if the number of affected rows is not available.
    long GetNumAffectedRows() const { return numAffectedRows_; }

    /// Return the column headers string collection.
    const StringVector& GetColumns() const { return columns_; }

    /// Return fetched rows collection. Filtered rows are not included in the collection.
    const Vector<VariantVector>& GetRows() const { return rows_; }

private:
    /// Column headers from the resultset.
    StringVector columns_;
    /// Fetched rows from the resultset.
    Vector<VariantVector> rows_;
    /// Number of affected rows by recent DML query.
    long numAffectedRows_;
};

}
