#include "algorithms.h"
#include <stdio.h>
#include <limits.h>

#define V 100

int graph[V][V];

void floydWarshall(int v, int g[V][V], int dist[V][V]) {
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            dist[i][j] = g[i][j];

    for (int k = 0; k < v; k++)
        for (int i = 0; i < v; i++)
            for (int j = 0; j < v; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}
// algorithms.h
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define V 100

extern int graph[V][V];
void floydWarshall(int v, int g[V][V], int dist[V][V]);

#endif
// gui.c
#include <gtk/gtk.h>
#include "algorithms.h"

void on_run_clicked(GtkWidget *widget, gpointer data) {
    int dist[V][V];
    floydWarshall(4, graph, dist);  // Adjust as needed

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            g_print("%d ", dist[i][j]);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Shortest Path GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_button_new_with_label("Run Floyd-Warshall");
    g_signal_connect(button, "clicked", G_CALLBACK(on_run_clicked), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
OBJS = gui.o algorithms.o

all: gui

gui: $(OBJS)
	$(CC) -o gui $(OBJS) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o gui
