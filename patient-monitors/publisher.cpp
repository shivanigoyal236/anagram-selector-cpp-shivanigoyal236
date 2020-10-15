#include "publisher.h"

static int disconnected = 0;
static int connected = 0;
static int published = 0;

struct pubsub_opts opts =
{
	1, 0, 0, 0, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT, "my_topic", "patient-monitors", 0, 0, NULL, NULL, "localhost", "1883", NULL, 10, /* MQTT options */
};



MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
MQTTProperty property;
MQTTProperties props = MQTTProperties_initializer;
MQTTAsync client;


int MessageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m)
{
	/* not expecting any messages */
	return 1;
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
	disconnected = 1;
}

void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	fprintf(stderr, "Connect failed, rc %s\n", response ? MQTTAsync_strerror(response->code) : "none");
	connected = -1;

	MQTTAsync client = (MQTTAsync)context;
}

void onConnect(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync) context;
	int rc = 0;

	if (opts.verbose)
		printf("Connected\n");

	connected = 1;
}

void onPublishFailure(void* context, MQTTAsync_failureData* response)
{
	if (opts.verbose)
		fprintf(stderr, "Publish failed, rc %s\n", MQTTAsync_strerror(response->code));
	published = -1;
}




void onPublish(void* context, MQTTAsync_successData* response)
{
	if (opts.verbose)
		printf("Publish succeeded\n");

	published = 1;
}


void myconnect(MQTTAsync client)
{
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	
	int rc = 0;

	if (opts.verbose)
		printf("Connecting\n");
	
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.cleansession = 1;
	
	conn_opts.keepAliveInterval = opts.keepalive;
	conn_opts.MQTTVersion = opts.MQTTVersion;
	conn_opts.context = client;
	conn_opts.automaticReconnect = 1;
    connected = 0;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		fprintf(stderr, "Failed to start connect, return code %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}

void Create_client(const char* url, MQTTAsync_createOptions* create_opts, MQTTAsync* client)
{
	int rc = MQTTAsync_createWithOptions(client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
		NULL, create_opts);
	if (rc != MQTTASYNC_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to create client, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}
void Set_Callback()
{
	int rc = MQTTAsync_setCallbacks(client, client, NULL, MessageArrived, NULL);
	if (rc != MQTTASYNC_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}
void Disconnect_Client(MQTTAsync_disconnectOptions disc_opts)
{
	int rc;
	disc_opts.onSuccess = onDisconnect;
	if ((rc = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to start disconnect, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

}
int mypublish(MQTTAsync client, int datalen, string data)
{
	int rc;

	if (opts.verbose)
		printf("Publishing data of length %d\n", datalen);
	rc = MQTTAsync_send(client, opts.topic, datalen, data.c_str(), opts.qos, opts.retained, &pub_opts);
	if (opts.verbose && rc != MQTTASYNC_SUCCESS && !opts.quiet)
		fprintf(stderr, "Error from MQTTAsync_send: %s\n", MQTTAsync_strerror(rc));

	return rc;
}
int publish(string s)
{
	int length = (int)s.length();
	int rc = mypublish(client, length, s);
	return rc;
}

int PUBLISHmain()
{
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	
	int url_allocated = 1;
	 const char* url = "localhost:1883";
	
	int rc = 0;
	
	printf("URL is %s\n", url);


	create_opts.sendWhileDisconnected = 1;
	Create_client(url, &create_opts, &client);
	Set_Callback();
	
	pub_opts.onSuccess = onPublish;
	pub_opts.onFailure = onPublishFailure;

	myconnect(client);
	return 0;
}


