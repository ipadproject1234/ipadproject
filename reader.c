#include <gtk/gtk.h>
#include <poppler.h>
#include <unistd.h>

#include "home.h"
#include "allFiles.h"

static void drawFunction(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data){
    PopplerPage *page = (PopplerPage *)user_data;

    double page_width, page_height;
    poppler_page_get_size(page, &page_width, &page_height);

    double scale = (double)width / page_width;
    cairo_scale(cr, scale, scale);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);
    poppler_page_render(page, cr);
}

void reader(GtkButton *btn, GtkWidget *window){
    GtkBuilder *builder;
    GError     *error = NULL;
    GtkWidget *overlay;
    GtkWidget *button;
    GtkWidget *scrolledWindow;
    GtkWidget *drawingArea;
    const char *fileName;
    PopplerDocument *document;
    PopplerPage *page;
    double page_width, page_height;
    char uri[512];
    char path[512];

    builder = gtk_builder_new();
    if(gtk_builder_add_from_file(builder, "../reader.ui", &error) == 0){
        g_printerr("Error loading ui: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    fileName = gtk_button_get_label(btn);
    realpath("../files", path);
    sprintf(uri, "file://%s/%s", path, fileName);
    printf("uri : %s\n", uri);


    document = poppler_document_new_from_file(uri, NULL, NULL);
    if (document == NULL) {
        g_printerr("Error: Could not open PDF file '%s'.\n", fileName);
        return;
    }

    page = poppler_document_get_page(document, 0);
    poppler_page_get_size(page, &page_width, &page_height);

    overlay = GTK_WIDGET(gtk_builder_get_object(builder, "overlay"));
    gtk_window_set_child(GTK_WINDOW(window), overlay);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "allFilesButton"));
    g_signal_connect(button, "clicked", G_CALLBACK(allFiles), window);

    scrolledWindow = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledWindow"));

    drawingArea = GTK_WIDGET(gtk_builder_get_object(builder, "drawingArea"));
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawingArea), (int)page_width);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawingArea), (int)page_height);

    gtk_widget_set_halign(drawingArea, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(drawingArea, GTK_ALIGN_START);

    gtk_drawing_area_set_draw_func(
        GTK_DRAWING_AREA(drawingArea),
        drawFunction,
        page,
        (GDestroyNotify)g_object_unref
    );

    gtk_window_present(GTK_WINDOW(window));
    g_object_unref(document);
    gtk_widget_queue_draw(drawingArea);
}
