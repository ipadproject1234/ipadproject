#include <gtk/gtk.h>

#include "allFiles.h"

static void temp_callback(GtkButton *button, gpointer user_data){
    const char *label = gtk_button_get_label(button);
    g_print("Temporary Action: %s clicked!\n", label);
}

void homeScreen(GtkApplicationWindow *window){

    GtkBuilder *builder;
    GtkWidget  *grid;
    GtkWidget *button;
    GError     *error = NULL;

    builder = gtk_builder_new();
    if(gtk_builder_add_from_file(builder, "../home.ui", &error) == 0){
        g_printerr("Error loading home_screen.ui: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    grid = GTK_WIDGET(gtk_builder_get_object(builder, "home_grid"));
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "filesButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(allFiles), window);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "helpButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(temp_callback), NULL);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "optionsButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(temp_callback), NULL);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "addButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(temp_callback), NULL);

    g_object_unref(builder);
}
