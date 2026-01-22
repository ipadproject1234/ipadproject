#include <gtk/gtk.h>

#include "home.h"
#include "reader.h"

static void temp_callback(GtkButton *button, gpointer user_data){
    const char *label = gtk_button_get_label(button);
    g_print("Temporary Action: %s clicked!\n", label);
}

void allFiles(GtkButton *btn, GtkWidget *window){
    GtkBuilder *builder;
    GtkWidget *scrolledWindow;
    GtkWidget *box;
    GtkWidget *button;
    GError *error = NULL;

    builder = gtk_builder_new();
    if(gtk_builder_add_from_file(builder, "../allFiles.ui", &error) == 0){
        g_printerr("Error loading subwindow.ui: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    scrolledWindow = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledWindow"));
    gtk_window_set_child(GTK_WINDOW(window), scrolledWindow);

    box = GTK_WIDGET(gtk_builder_get_object(builder, "box"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "homeButton"));
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(homeScreen), window);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "addFileButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(temp_callback), NULL);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "deleteFileButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(temp_callback), NULL);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "testPdfButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(reader), window);

    gtk_window_present(GTK_WINDOW(window));

    g_object_unref(builder);
}
