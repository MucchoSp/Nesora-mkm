#ifndef NESORA_MANAGER_TREE_CTRL_DATA_H
#define NESORA_MANAGER_TREE_CTRL_DATA_H

#include <string>

#include <wx/wx.h>

class NesoraTreeItemData: public wxTreeItemData
{
friend class WXDLLIMPEXP_FWD_CORE wxTreeCtrl;
friend class WXDLLIMPEXP_FWD_CORE wxGenericTreeCtrl;
public:
    // creation/destruction
    // --------------------
        // default ctor
    NesoraTreeItemData() = default;

        // default copy ctor/assignment operator are ok
    NesoraTreeItemData(const std::string& str) {
        path = str;
    }

    // accessor: get the item associated with us
    const wxTreeItemId& GetId() const { return m_pItem; }
    void SetId(const wxTreeItemId& id) { m_pItem = id; }

    const std::string &GetPath() const { return path; }

protected:
    wxTreeItemId m_pItem;
    std::string path;
};

#endif //NESORA_MANAGER_TREE_CTRL_DATA_H
