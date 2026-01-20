#include <gtk/gtk.h>
#include <poppler.h>
#include <unistd.h>
#include <string.h>

static void homeScreen(GtkButton *button, GtkWidget *window);
char path[200];

//////////////////////
// HELPER FUNCTIONS //
//////////////////////

// help function for drawing area
static void drawFunction(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data){
    PopplerPage *page = (PopplerPage *)user_data;
    double page_width, page_height;
    poppler_page_get_size(page, &page_width, &page_height);
    double scale = (double)width / page_width;
    cairo_scale(cr, scale, scale);
    poppler_page_render(page, cr);
}

//////////////////////////////
// WINDOWS/BUTTON FUNCTIONS //
////////////////////////////// 

// pdf reader
static void reader(GtkButton *button, GtkWidget *window){
    GtkWidget *box;
    GtkWidget *scrolledWindow;
    GtkWidget *drawingArea;
    const char *fileName;
    PopplerDocument *document;
    PopplerPage *page;
    double page_width, page_height;
    char uri[512];

    fileName = gtk_button_get_label(button);
    sprintf(uri, "file://%s%s", path, fileName);

    document = poppler_document_new_from_file(uri, NULL, NULL);

    if (document == NULL) {
        g_printerr("Error: Could not open PDF file '%s'.\n", fileName);
        return;
    }

    page = poppler_document_get_page(document, 0);
    poppler_page_get_size(page, &page_width, &page_height);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, TRUE);
    gtk_widget_set_hexpand(scrolledWindow, TRUE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_box_append(GTK_BOX(box), scrolledWindow);

    drawingArea = gtk_drawing_area_new();
    gtk_widget_set_hexpand(drawingArea, TRUE);
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawingArea), (int)page_width);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawingArea), (int)page_height);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), drawingArea);
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

//temp
static void tempButtonClick(GtkButton *button){
    const char *buttonName;

    buttonName = gtk_button_get_label(button);
    if(g_strcmp0(buttonName, "Hello.") == 0)
        gtk_button_set_label(button, "Good-bye.");
    else
        gtk_button_set_label(button, "Hello.");
}

//Close window
static void closeWindow(GtkButton *button, GtkWindow *window){
    gtk_window_destroy(window);
}

// files button
static void filesWindow(GtkButton *button, GtkWidget *window){
    GtkWidget *box;
    GtkWidget *scrolledWindow;
    GtkWidget *backButton;
    GtkWidget *testpdf;
    GtkWidget *addButton;

    scrolledWindow = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolledWindow, TRUE);
    gtk_widget_set_hexpand(scrolledWindow, TRUE);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledWindow),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolledWindow);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolledWindow), box);

    backButton = gtk_button_new_with_label("Back");
    g_signal_connect(backButton, "clicked", G_CALLBACK(homeScreen), window);

    testpdf = gtk_button_new_with_label("testpdf.pdf");
    g_signal_connect(testpdf, "clicked", G_CALLBACK(reader), window);

    //addButton
    //for each file imported, ask to put in folder
    addButton = gtk_button_new_with_label("add new file");
    g_signal_connect(addButton, "clicked", G_CALLBACK(tempButtonClick), NULL);

    gtk_box_append(GTK_BOX(box), backButton);
    gtk_box_append(GTK_BOX(box), testpdf);
    gtk_box_append(GTK_BOX(box), addButton);
}

static void homeScreen(GtkButton *button, GtkWidget *window){
    GtkWidget *grid;
    GtkWidget *filesButton;
    GtkWidget *optionsButton;
    GtkWidget *addButton;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

    filesButton = gtk_button_new_with_label("Files");
    g_signal_connect(filesButton, "clicked", G_CALLBACK(filesWindow), window);

    optionsButton = gtk_button_new_with_label("Options");
    g_signal_connect(optionsButton, "clicked", G_CALLBACK(tempButtonClick), NULL);

    addButton = gtk_button_new_with_label("add new folder");
    g_signal_connect(addButton, "clicked", G_CALLBACK(tempButtonClick), NULL);

    button1 = gtk_button_new_with_label("temp");
    g_signal_connect(button1, "clicked", G_CALLBACK(tempButtonClick), NULL);

    button2 = gtk_button_new_with_label("temp");
    g_signal_connect(button2, "clicked", G_CALLBACK(tempButtonClick), NULL);

    button3 = gtk_button_new_with_label("temp");
    g_signal_connect(button3, "clicked", G_CALLBACK(tempButtonClick), NULL);


    gtk_grid_attach(GTK_GRID(grid), filesButton, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), optionsButton, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), addButton, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button1, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button3, 1, 1, 1, 1);
}

//activate
static void app_activate(GApplication *app){
    GtkWidget *window;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "lb4");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    homeScreen(NULL, window);

    gtk_window_present(GTK_WINDOW(window));
}

//////////
// MAIN //
//////////

int main(int argc, char **argv){

    GtkApplication *app;
    int status;

    getcwd(path, sizeof(path));
    while(path[strlen(path) - 1] != '/'){
        path[strlen(path) - 1] = '\0';
    }
    strcat(path, "files/");
    printf("%s\n", path);

    app = gtk_application_new("com.test", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
