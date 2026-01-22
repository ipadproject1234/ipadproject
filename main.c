#include <gtk/gtk.h>

#include "allFiles.h"
#include "home.h"

static void app_activate(GApplication *app){
    GtkWidget *window;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "GTK 4 XML Home Screen");

    homeScreen(GTK_APPLICATION_WINDOW(window));

    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv){
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.test.xmlversion", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
