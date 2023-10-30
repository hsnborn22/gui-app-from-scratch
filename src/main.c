#define _GNU_SOURCE
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include "jsonParser.h"
#include "httpsClient.h"

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *button1;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *entry1;
GtkBuilder*builder;

int main(int argc, char ** argv) {
	gtk_init(&argc,&argv);
	builder = gtk_builder_new_from_file("main.xml");
	window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));

	g_signal_connect(window,"destroy", G_CALLBACK(gtk_main_quit),NULL);
	
	gtk_builder_connect_signals(builder,NULL);
	
	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
	button1= GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder,"label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder,"label2"));
	entry1  = GTK_WIDGET(gtk_builder_get_object(builder,"entry1"));
	
	gtk_widget_show(window);
	gtk_main();

	return EXIT_SUCCESS;

}

void on_button1_clicked(GtkButton *b) {
	const gchar* buffer = gtk_entry_get_text(GTK_ENTRY(entry1));
	char * rawResponse = findJsonByName((char *)buffer);
	char * jsonResponse = getJsonFromRawResponse(rawResponse);
	json_object * parsedJson = parseJson(jsonResponse);


	gtk_label_set_text(GTK_LABEL(label1), (const gchar*)parsedJson->keyList[2].value);
	gtk_label_set_text(GTK_LABEL(label2), (const gchar*)parsedJson->keyList[3].value);
}