
#if !defined(PUBSUB_OPTS_H)
#define PUBSUB_OPTS_H

#include "MQTTAsync.h"
#include "MQTTClientPersistence.h"

struct pubsub_opts
{
	/* debug app options */
	int publisher;  /* publisher app? */
	int quiet;
	int verbose;
	int tracelevel;
	const char* delimiter;
	int maxdatalen;
	/* message options */
	char* message;
	char* filename;
	int stdin_lines;
	int stdlin_complete;
	int null_message;
	/* MQTT options */
	int MQTTVersion;
	const char* topic;
	const char* clientid;
	int qos;
	int retained;
	char* username;
	char* password;
	const char* host;
	const char* port;
	char* connection;
	int keepalive;
	
};

typedef struct
{
	const char* name;
	const char* value;
} pubsub_opts_nameValue;



#endif


