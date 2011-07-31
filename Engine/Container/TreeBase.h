//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse Öörni
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

#include "Allocator.h"
#include "Swap.h"

// Based on Red Black Trees by Julienne Walker
// http://eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx

/// Red-black tree node base
struct TreeNodeBase
{
    /// Construct
    TreeNodeBase() :
        parent_(0),
        isRed_(true)
    {
        link_[0] = 0;
        link_[1] = 0;
    }
    
    /// %Set a child link, adjusting the child's parent as necessary
    void SetChild(unsigned dir, TreeNodeBase* newChild)
    {
        link_[dir] = newChild;
        if (newChild)
            newChild->parent_ = this;
    }
    
    /// Parent node
    TreeNodeBase* parent_;
    /// Child links
    TreeNodeBase* link_[2];
    /// Color flag
    bool isRed_;
};

/// Red-black tree iterator base class
class TreeIteratorBase
{
public:
    /// Construct
    TreeIteratorBase() :
        ptr_(0),
        prev_(0)
    {
    }
    
    /// Construct with a node pointer
    TreeIteratorBase(TreeNodeBase* ptr) :
        ptr_(ptr),
        prev_(0)
    {
    }
    
    /// Test for equality with another iterator
    bool operator == (const TreeIteratorBase& rhs) const { return ptr_ == rhs.ptr_; }
    /// Test for inequality with another iterator
    bool operator != (const TreeIteratorBase& rhs) const { return ptr_ != rhs.ptr_; }
    
    /// Go to the next node
    void GotoNext()
    {
        if (!ptr_)
        {
            prev_ = 0;
            return;
        }
        
        prev_ = ptr_;
        
        if (!ptr_->link_[1])
        {
            while (ptr_->parent_ && ptr_->parent_->link_[1] == ptr_)
                ptr_ = ptr_->parent_;
            
            ptr_ = ptr_->parent_;
            return;
        }
        
        ptr_ = ptr_->link_[1];
        while (ptr_->link_[0])
            ptr_ = ptr_->link_[0];
    }
    
    /// Go to the previous node
    void GotoPrev()
    {
        if (!ptr_)
        {
            ptr_ = prev_;
            prev_ = 0;
            return;
        }
        
        prev_ = 0;
        
        if (!ptr_->link_[0])
        {
            while (ptr_->parent_ && ptr_->parent_->link_[0] == ptr_)
                ptr_ = ptr_->parent_;
            
            ptr_ = ptr_->parent_;
            return;
        }
        
        ptr_ = ptr_->link_[0];
        while (ptr_->link_[1])
            ptr_ = ptr_->link_[1];
    }
    
    /// Current node pointer
    TreeNodeBase* ptr_;
    /// Previous node pointer, needed to back from the end
    TreeNodeBase* prev_;
};

/// Red-black tree base class
class TreeBase
{
public:
    /// Construct
    TreeBase() :
        root_(0),
        allocator_(0),
        size_(0)
    {
    }
    
    /// Swap with another tree
    void Swap(TreeBase& rhs)
    {
        ::Swap(root_, rhs.root_);
        ::Swap(allocator_, rhs.allocator_);
        ::Swap(size_, rhs.size_);
    }
    
protected:
    /// Check whether a node is red
    bool IsRed(TreeNodeBase* node) const { return node && node->isRed_; }
    
    /// Single rotation
    TreeNodeBase* RotateSingle(TreeNodeBase* node, unsigned dir)
    {
        TreeNodeBase* save = node->link_[!dir];
        
        node->SetChild(!dir, save->link_[dir]);
        save->SetChild(dir, node);
        
        node->isRed_ = true;
        save->isRed_ = false;
        
        return save;
    }
    
    /// Double rotation
    TreeNodeBase* RotateDouble(TreeNodeBase* node, unsigned dir)
    {
        node->SetChild(!dir, RotateSingle(node->link_[!dir], !dir));
        return RotateSingle(node, dir);
    }
    
    /// Root node
    TreeNodeBase* root_;
    /// Node allocator
    AllocatorBlock* allocator_;
    /// Number of nodes
    unsigned size_;
};
