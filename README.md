# dirtnoise
Listen to how dirty the air is around you.

Dirtnoise is a small, non-serious, and hacky proof-of-concept that generates random saw waves based on the air quality of a specified location. It is a bit like an air-quality Geiger counter.
The locations it takes as an argument are those found in the OpenAQ API.

Dirtnoise uses much of the code of the OpenAQ_CLI repo for its API-querying and parsing. 

Libraries used are Jansson (for JSON parsing), Curl (HTTP requests), and PortAudio (sound API).
