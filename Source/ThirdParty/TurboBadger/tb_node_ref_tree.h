// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_NODE_REF_TREE_H
#define TB_NODE_REF_TREE_H

#include "tb_linklist.h"
#include "tb_node_tree.h"
#include "tb_id.h"

namespace tb {

class TBNode;
class TBNodeRefTreeListener;

/** TBNodeRefTree is a named TBNode.
	Nodes under this node may be referenced from other nodes, either when
	requesting a value (TBNode::GetValueFollowRef), or while parsing the
	node tree. While parsing, the values can be used for branch conditions
	or branches of nodes can be included. */
class TBNodeRefTree : public TBLinkOf<TBNodeRefTree>
{
public:
	TBNodeRefTree(const char *name);
	virtual ~TBNodeRefTree();

	const char *GetName() const { return m_name; }
	const TBID &GetNameID() const { return m_name_id; }

	/** Read the data file. This will *not* invoke any change listener! */
	bool ReadFile(const char *filename) { return m_node.ReadFile(filename); }
	void ReadData(const char *data) { m_node.ReadData(data); }

	/** Add a listener that is invoked on changes in this tree. */
	void AddListener(TBNodeRefTreeListener *listener) { m_listeners.AddLast(listener); }

	/** Remove a change listener from this tree. */
	void RemoveListener(TBNodeRefTreeListener *listener) { m_listeners.Remove(listener); }

	/** Set the value for the given request and invoke the change listener.
		Creates the nodes that doesn't exist. */
	virtual void SetValue(const char *request, const TBValue &value);

	/** Get the value of the given request. Follows references if any.
		Returns a null value if the request doesn't exist. */
	virtual TBValue &GetValue(const char *request);

	/** Get the value of the given tree name and request (@treename>noderequest).
		Returns a null value if the given tree or request doesn't exist. */
	static TBValue &GetValueFromTree(const char *request);

	/** Return the tree with the given name, or nullptr if no matching tree exists. */
	static TBNodeRefTree *GetRefTree(const char *name, int name_len);

	/** Go through the tree of nodes recursively and include
		or remove branches depending on any conditions. */
	static void ResolveConditions(TBNode *parent_node);
private:
	friend class TBNode;
	friend class TBNodeTarget;
	/** Follow any references to data trees and return the destination node.
		If there's broken references, the node will be returned. */
	static TBNode *FollowNodeRef(TBNode *node);

	void InvokeChangeListenersInternal(const char *request);
	TBNode m_node;
	TBStr m_name;
	TBID m_name_id;
	TBLinkListOf<TBNodeRefTreeListener> m_listeners;
	static TBLinkListOf<TBNodeRefTree> s_ref_trees;
};

/**	TBNodeRefTreeListener receive OnDataChanged when the
	value of a node in a TBNodeRefTree is changed.
	FIX: The listener can currently only listen to one tree. */
class TBNodeRefTreeListener : public TBLinkOf<TBNodeRefTreeListener>
{
public:
	/** Called when the value is changed for the given node
		in the given ref tree. The request is without tree name. */
	virtual void OnDataChanged(TBNodeRefTree *rt, const char *request) = 0;
};

}; // namespace tb

#endif // TB_NODE_REF_TREE_H
