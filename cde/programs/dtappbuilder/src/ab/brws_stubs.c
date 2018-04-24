/*** DTB_USER_CODE_START vvv Add file header below vvv ***/
/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/*** DTB_USER_CODE_END   ^^^ Add file header above ^^^ ***/

/*
 * File: brws_stubs.c
 * Contains: Module callbacks and connection functions
 *
 * This file was generated by dtcodegen, from module brws
 *
 * Any text may be added between the DTB_USER_CODE_START and
 * DTB_USER_CODE_END comments (even non-C code). Descriptive comments
 * are provided only as an aid.
 *
 *  ** EDIT ONLY WITHIN SECTIONS MARKED WITH DTB_USER_CODE COMMENTS.  **
 *  ** ALL OTHER MODIFICATIONS WILL BE OVERWRITTEN. DO NOT MODIFY OR  **
 *  ** DELETE THE GENERATED COMMENTS!                                 **
 */

#include <stdint.h>
#include <stdio.h>
#include <Xm/Xm.h>
#include "dtb_utils.h"
#include "dtbuilder.h"
#include "brws_ui.h"


/**************************************************************************
 *** DTB_USER_CODE_START
 ***
 *** All necessary header files have been included.
 ***
 *** Add include files, types, macros, externs, and user functions here.
 ***/

#include <ab_private/abobj_edit.h>
#include <ab_private/util.h>
#include "dtbuilder.h"
#include "brws.h"
#include "brwsP.h"
#include "brws_ui.h"
#include "projP.h"
#include "dtb_utils.h"

/*
 * Declarations of global widgets used by callbacks.
 */
/*
 * End declarations of global widgets
 */


/*** DTB_USER_CODE_END
 ***
 *** End of user code section
 ***
 **************************************************************************/



void 
brws_help_pulldown_Overview_item_CB1(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    dtb_show_help_volume_info("AppBuilder", "ABBrowser");
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brws_help_pulldown_Tasks_item_CB1(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    dtb_show_help_volume_info("AppBuilder", "ABBrowser");
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brws_help_pulldown_Reference_item_CB1(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    dtb_show_help_volume_info("AppBuilder", "ABBrowser");
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brws_help_pulldown_Using_Help_item_CB1(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    dtb_show_help_volume_info("Help4Help", "_hometopic");
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brws_help_pulldown_On_Item_item_CB1(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    dtb_do_onitem_help();
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_orientation(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser           ab = NULL;
    BrowserProps        props;
    XmString            xmlabel;
    char		*str;

    XtVaGetValues(widget, XmNuserData, &ab, NULL);

    props = aob_browser_properties(ab->module);

    if (props->orientation == BRWS_VERTICAL)  {
        props->orientation = BRWS_HORIZONTAL;
        str = catgets(Dtb_project_catd, 100, 66, "Vertical");
        xmlabel = XmStringCreateLocalized(str);
    }
    else  {
        props->orientation = BRWS_VERTICAL;
        str = catgets(Dtb_project_catd, 100, 67, "Horizontal");
        xmlabel = XmStringCreateLocalized(str);
    }

    XtVaSetValues(widget, XmNlabelString, xmlabel, NULL);

    XmStringFree(xmlabel);

    erase_viewer(ab->module);
    draw_viewer(ab->module);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_obj_glyph(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser   ab = NULL;
    char	*hide_str = NULL,
		*show_str = NULL;

    XtVaGetValues(widget, XmNuserData, &ab, NULL);

    if (!ab || !ab->module)
        return;

    hide_str = XtNewString(catgets(Dtb_project_catd, 100, 60, 
	"Hide Object Glyph"));
    show_str = XtNewString(catgets(Dtb_project_catd, 100, 61, 
	"Show Object Glyph"));

    browser_show_view_elements(ab->module,
                BRWS_SHOW_GLYPH, widget, hide_str, show_str);

    XtFree(hide_str);
    XtFree(show_str);
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_obj_class(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser   b = NULL;
    char	*hide_str = NULL,
		*show_str = NULL;

    XtVaGetValues(widget, XmNuserData, &b, NULL);

    if (!b || !b->module)
        return;

    hide_str = XtNewString(catgets(Dtb_project_catd, 100, 62, 
	"Hide Object Type"));
    show_str = XtNewString(catgets(Dtb_project_catd, 100, 63, 
	"Show Object Type"));

    browser_show_view_elements(b->module,
                BRWS_SHOW_TYPE, widget, hide_str, show_str);

    XtFree(hide_str);
    XtFree(show_str);
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_obj_name(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser   ab = NULL;
    char	*hide_str = NULL,
		*show_str = NULL;

    XtVaGetValues(widget, XmNuserData, &ab, NULL);

    if (!ab || !ab->module)
        return;

    hide_str = XtNewString(catgets(Dtb_project_catd, 100, 64, 
	"Hide Object Name"));
    show_str = XtNewString(catgets(Dtb_project_catd, 100, 65, 
	"Show Object Name"));

    browser_show_view_elements(ab->module,
                BRWS_SHOW_NAME, widget, hide_str, show_str);

    XtFree(hide_str);
    XtFree(show_str);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_find(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser           b = NULL;
    Vwr                 v;
    BrowserUiObj        ui;

    XtVaGetValues(widget, XmNuserData, &b, NULL);
    v = b->module;

    ui = aob_ui_from_browser(v);

    if (!ui->find_box)
    {
        brwsP_create_find_box(b);
    }

    brwsP_show_find_box(v);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_undo(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    (void)abobj_undo();

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_cut(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    (void)abobj_cut();

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_copy(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    (void)abobj_copy();

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_paste(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    (void)abobj_paste(AB_PASTE_INITIATOR_BRWS_EDIT_MENU);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_delete(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    (void)abobj_delete();

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_toplevel_repaint(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser   ab = NULL;
    Vwr         b;

    XtVaGetValues(widget, XmNuserData, &ab, NULL);

    b = aob_proj_or_module(ab, widget);

    /*
     * Don't call repaint proc if no project associated with
     * browser yet
     */
    if (!b->obj_data)
        return;

    vwr_repaint(b);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_detailed_repaint(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser   ab = NULL;
    Vwr         b;

    XtVaGetValues(widget, XmNuserData, &ab, NULL);

    b = aob_proj_or_module(ab, widget);

    /*
     * Don't call repaint proc if no project associated with
     * browser yet
     */
    if (!b->obj_data)
        return;

    vwr_repaint(b);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_detailed_resize(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    /*
     * Will remove this function soon
     */
    return;

    /*
    ABBrowser   ab = NULL;
    Vwr         b;

    XtVaGetValues(widget, XmNuserData, &ab, NULL);

    b = aob_proj_or_module(ab, widget);

    recompute_viewer(b);
    */

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_collapse(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser	ab = NULL;

    XtVaGetValues(widget, XmNuserData, &ab, NULL); 
    
    brwsP_collapse_selected(ab);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_expand(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser	ab = NULL;

    XtVaGetValues(widget, XmNuserData, &ab, NULL); 
    
    brwsP_expand_selected(ab);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_expandAll(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser	ab = NULL;

    XtVaGetValues(widget, XmNuserData, &ab, NULL); 

    brwsP_expand_collapsed(ab);
    
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_tear_off(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/

    ABBrowser		b = NULL;

    XtVaGetValues(widget, XmNuserData, &b, NULL); 

    brwsP_tear_off_selected(b);

    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}


void 
brwsP_close(
    Widget widget,
    XtPointer clientData,
    XtPointer callData
)
{
    /*** DTB_USER_CODE_START vvv Add C variables and code below vvv ***/
    DtbBrwsMainwindowInfo	instance = (DtbBrwsMainwindowInfo)clientData;
    Widget	shell;
    /*** DTB_USER_CODE_END   ^^^ Add C variables and code above ^^^ ***/
    
    /*** DTB_USER_CODE_START vvv Add C code below vvv ***/
    /*
     * Return right away if instance ptr is NULL
     * or if the instance struct is not initialized
     * or the 'mainwindow' field is NULL
     */
    if (!instance || !instance->initialized || !instance->mainwindow)
	return;

    /*
     * Get parent shell
     */
    shell = ui_get_ancestor_shell(instance->mainwindow);

    /*
     * Destroy browser shell widget. This will trigger destroy
     * callbacks that will do some cleanup
     */
    if (shell)
        XtDestroyWidget(shell);
    /*** DTB_USER_CODE_END   ^^^ Add C code above ^^^ ***/
}



/**************************************************************************
 *** DTB_USER_CODE_START
 ***
 *** All automatically-generated data and functions have been defined.
 ***
 *** Add new functions here, or at the top of the file.
 ***/
/*** DTB_USER_CODE_END
 ***
 *** End of user code section
 ***
 **************************************************************************/


