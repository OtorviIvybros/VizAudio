/**
* Project: VizAudio
* File name: prop_parse.c
* Description: This is simply a test program for visual effects
* 
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Ryan Gee
* @author       Rachel Foecking
* @author		Foster Nichols
* @copyright    Humanitarian FOSS Project (http://www.hfoss.org), Copyright (C) 2009.
* @package
* @subpackage
* @tutorial
* @license  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
* @version
*/

#include <gtk/gtk.h>
#include <canberra-gtk.h>

/* Destroys the window. Wrapped to facilitate timing from
 * g_timeout_add() */
static gboolean endFlash(GtkWidget *window){
    gtk_object_destroy(GTK_OBJECT(window));
    return FALSE;
}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void hello( GtkWidget *widget,
                   gpointer   data )
{
    g_print ("Hello World\n");
    ca_context_play (ca_gtk_context_get (), 0,
			 CA_PROP_EVENT_ID, "button-pressed",
			 CA_PROP_EVENT_DESCRIPTION, "haha description",NULL);
    
    /* Create a temporary, decorationless window */
    GtkWidget* tempFlashWindow;
    tempFlashWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(tempFlashWindow), FALSE);
    //gtk_window_fullscreen(GTK_WINDOW(tempFlashWindow));
    gtk_window_set_position(GTK_WINDOW(tempFlashWindow), GTK_WIN_POS_CENTER);
    
    /* Modify the color of the window 
    GdkColor color;
    gdk_color_parse("light blue", &color);
    gtk_widget_modify_bg(tempFlashWindow, GTK_STATE_NORMAL, &color);*/
    
    GtkWidget* image;
    image = gtk_image_new_from_file("seaslug.jpg");
    gtk_container_add (GTK_CONTAINER (tempFlashWindow), image);
    
    gtk_widget_show(image);    
    gtk_widget_show(tempFlashWindow);
    
    
    /* This function takes the function endFlash and calls it every
     * 1 second. When endFlash returns false, this loop ends.
     * This serves to make the screen flash last only one second. */
    g_timeout_add(1000, (GSourceFunc)endFlash, (gpointer)tempFlashWindow);
}

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete_event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");
   
    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete_event". */

    return FALSE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

int main( int   argc,
          char *argv[] )
{
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *button;
    
    /* This is called in all GTK applications. Arguments are parsed
     * from the command line and are returned to the application. */
    gtk_init (&argc, &argv);
    
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_resize(GTK_WINDOW(window), 200, 100);    

    /* When the window is given the "delete_event" signal (this is given
     * by the window manager, usually by the "close" option, or on the
     * titlebar), we ask it to call the delete_event () function
     * as defined above. The data passed to the callback
     * function is NULL and is ignored in the callback function. */
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (delete_event), NULL);
    
    /* Here we connect the "destroy" event to a signal handler.  
     * This event occurs when we call gtk_widget_destroy() on the window,
     * or if we return FALSE in the "delete_event" callback. */
    g_signal_connect (G_OBJECT (window), "destroy",
		      G_CALLBACK (destroy), NULL);
    
    /* Sets the border width of the window. */
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    /* Creates a new button with the label "Hello World". */
    button = gtk_button_new_with_label ("Hello World");
    
    /* When the button receives the "clicked" signal, it will call the
     * function hello() passing it NULL as its argument.  The hello()
     * function is defined above. */
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (hello), NULL);
    
    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked".  Again, the destroy
     * signal could come from here, or the window manager. */
    /*g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_widget_destroy),
                              G_OBJECT (window));*/
    
    /* This packs the button into the window (a gtk container). */
    gtk_container_add (GTK_CONTAINER (window), button);
    
    /* The final step is to display this newly created widget. */
    gtk_widget_show (button);
    
    /* and the window */
    gtk_widget_show (window);
    
    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main ();
    
    return 0;
}
