
# include "subscriber.h"
#include "patientInfo.h"
extern void saveDataToCSV(string);
extern int patientcount();
extern void setPatientInfoOnSubscriber(string);

volatile int finished = 0;
int subscribed = 0;
int disconnected = 0;
patientInfo subscriberPatientInfo;
MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;

struct pubsub_opts subopts =
{
	0, 0, 0, MQTTASYNC_TRACE_MAXIMUM, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT,"my_topic", "patient-monitors1", 0, 0, NULL, NULL, "localhost", "1883", NULL, 10, /* MQTT options */
};

int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
	size_t delimlen = 0;
	printf("%.*s\n", message->payloadlen, (char*)message->payload);
	subscriberPatientInfo.setReceivedString((char*)message->payload);
	saveDataToCSV((char*)message->payload);
	fflush(stdout);
	MQTTAsync_freeMessage(&message);
	MQTTAsync_free(topicName);
	return 1;
}

void OnDisconnect(void* context, MQTTAsync_successData* response)
{
	disconnected = 1;
}

void OnSubscribe(void* context, MQTTAsync_successData* response)
{
	subscribed = 1;
}


void OnSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	if (!subopts.quiet)
		fprintf(stderr, "Subscribe failed, rc %s\n",
			MQTTAsync_strerror(response->code));
	finished = 1;
}


void OnConnectFailure(void* context, MQTTAsync_failureData* response)
{
	if (!subopts.quiet)
		fprintf(stderr, "Connect failed, rc %s\n", response ? MQTTAsync_strerror(response->code) : "none");
	finished = 1;
}


void OnConnect(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions ropts = MQTTAsync_responseOptions_initializer;
	int rc;

	printf("\nSubscribing to topic %s with client %s at QoS %d\n", subopts.topic, subopts.clientid, subopts.qos);

	ropts.onSuccess = OnSubscribe;
	ropts.onFailure = OnSubscribeFailure;
	ropts.context = client;
	if ((rc = MQTTAsync_subscribe(client, subopts.topic, subopts.qos, &ropts)) != MQTTASYNC_SUCCESS)
	{
		if (!subopts.quiet)
			fprintf(stderr, "Failed to start subscribe, return code %s\n", MQTTAsync_strerror(rc));
		finished = 1;
	}
	else
		printf("subscribed\n");
}
void Create_Client(const char* url, MQTTAsync_createOptions *create_opts, MQTTAsync *client)
{
	int rc = MQTTAsync_createWithOptions(client, url, subopts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
		NULL, create_opts);
	if (rc != MQTTASYNC_SUCCESS)
	{
		if (!subopts.quiet)
			fprintf(stderr, "Failed to create client, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}
void Set_Callback(MQTTAsync client)
{
	int rc = MQTTAsync_setCallbacks(client, client, NULL, messageArrived, NULL);
	if (rc != MQTTASYNC_SUCCESS)
	{
		if (!subopts.quiet)
			fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}
}
void disconnect_Client(MQTTAsync_disconnectOptions disc_opts, MQTTAsync client)
{
	int rc;
	disc_opts.onSuccess = OnDisconnect;
	if ((rc = MQTTAsync_disconnect(client, &disc_opts)) != MQTTASYNC_SUCCESS)
	{
		if (!subopts.quiet)
			fprintf(stderr, "Failed to start disconnect, return code: %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

}
int SUBSCRIBEmain()
{
	MQTTAsync client;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	MQTTAsync_createOptions create_opts = MQTTAsync_createOptions_initializer;
	int rc = 0;
	const char* url = "localhost:1883";
	printf("URL is %s\n", url);
	Create_Client(url, &create_opts,&client);
	Set_Callback(client);
	conn_opts.onSuccess = OnConnect;
	conn_opts.onFailure = OnConnectFailure;
	conn_opts.cleansession = 1;
	
	conn_opts.keepAliveInterval = subopts.keepalive;
	conn_opts.MQTTVersion = subopts.MQTTVersion;
	conn_opts.context = client;
	conn_opts.automaticReconnect = 1;

	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		if (!subopts.quiet)
			fprintf(stderr, "Failed to start connect, return code %s\n", MQTTAsync_strerror(rc));
		exit(EXIT_FAILURE);
	}

	while (!subscribed)
		sleep(100);

	
	return 0;
}
