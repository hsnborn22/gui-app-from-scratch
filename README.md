# gender-determining-app
A GUI name gender determining app written in C with my own json parser and https client: the only third party dependencies I used are openssl and gtk.
The app determines the gender and the probability of a name being that gender using the api.genderize.io API. The application makes a request to the API via an HTTP over TLS socket request, gets the JSON back from the application, parses it and displays it on the GUI.
