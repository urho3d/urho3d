//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../../Core/Variant.h"

#include <nanodbc/nanodbc.h>

namespace Urho3D
{

/// %Database query result.
class URHO3D_API DbResult
{
    friend class DbConnection;

public:
    /// Return number of columns in the resultset or 0 if there is no resultset.
    int NumColumns() const { return columns_.Size(); }

    /// Return number of rows in the resultset or 0 if the number of rows is not available.
    long NumRows() const { return rows_.Size(); }

    /// Return number of affected rows by the DML query or -1 if the number of affected rows is not available.
    long NumAffectedRows() const { return resultImpl_ ? resultImpl_.affected_rows() : -1; }

    /// Return the underlying implementation result object.
    const nanodbc::result& GetResultImpl() const { return resultImpl_; }

    /// Return the column headers string collection.
    const Vector<String>& GetColumns() const { return columns_; }

    /// Return fetched rows collection. Filtered rows are not included in the collection.
    const Vector<VariantVector>& GetRows() const { return rows_; }

private:
    /// The underlying implementation connection object.
    nanodbc::result resultImpl_;
    /// Column headers from the resultset.
    Vector<String> columns_;
    /// Fetched rows from the resultset.
    Vector<VariantVector> rows_;
};

}
