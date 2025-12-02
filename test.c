#include <gtk/gtk.h>

//////////////////////////////
// WINDOWS/BUTTON FUNCTIONS //
////////////////////////////// 

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

//temp
static void filesButton(GtkButton *button, GtkWidget *window){
    GtkWidget *box;
    GtkWidget *button1;
    GtkWidget *closeButton;
    GtkWidget *button2;
    GtkWidget *button3;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);
    gtk_window_set_child(GTK_WINDOW(window), box);

    button1 = gtk_button_new_with_label("button1");
    g_signal_connect(button1, "clicked", G_CALLBACK(tempButtonClick), NULL);

    closeButton = gtk_button_new_with_label("Close");
    g_signal_connect(closeButton, "clicked", G_CALLBACK(closeWindow), window);

    button2 = gtk_button_new_with_label("button3");
    g_signal_connect(button2, "clicked", G_CALLBACK(tempButtonClick), NULL);

    button3 = gtk_button_new_with_label("button4");
    g_signal_connect(button3, "clicked", G_CALLBACK(tempButtonClick), NULL);

    gtk_box_append(GTK_BOX(box), button1);
    gtk_box_append(GTK_BOX(box), closeButton);
    gtk_box_append(GTK_BOX(box), button2);
    gtk_box_append(GTK_BOX(box), button3);
}

//initial screen
static void app_activate(GApplication *app){
    GtkWidget *window;
    GtkWidget *mainBox;
    GtkWidget *menuBox;
    GtkWidget *contentBox;
    GtkWidget *button1;
    GtkWidget *closeButton;
    GtkWidget *button2;
    GtkWidget *button3;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "lb4");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(window), mainBox);

    menuBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(menuBox), TRUE);

    contentBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(contentBox), TRUE);

    button1 = gtk_button_new_with_label("Files");
    g_signal_connect(button1, "clicked", G_CALLBACK(filesButton), window);

    closeButton = gtk_button_new_with_label("Close");
    g_signal_connect(closeButton, "clicked", G_CALLBACK(closeWindow), window);

    button2 = gtk_button_new_with_label("Hello.");
    g_signal_connect(button2, "clicked", G_CALLBACK(tempButtonClick), NULL);

    button3 = gtk_button_new_with_label("Hello.");
    g_signal_connect(button3, "clicked", G_CALLBACK(tempButtonClick), NULL);

    gtk_box_append(GTK_BOX(mainBox), menuBox);
    gtk_box_append(GTK_BOX(mainBox), contentBox);

    gtk_box_append(GTK_BOX(menuBox), button1);
    gtk_box_append(GTK_BOX(menuBox), button2);
    gtk_box_append(GTK_BOX(menuBox), button3);
    gtk_box_append(GTK_BOX(menuBox), closeButton);

    gtk_window_present(GTK_WINDOW(window));
}

//////////
// MAIN //
//////////

int main(int argc, char **argv){

    GtkApplication *app;
    int status;

    app = gtk_application_new("com.test", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
