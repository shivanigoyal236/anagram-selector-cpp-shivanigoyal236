#pragma once
#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"
#include "MQTTAsync.h"
#include "pubsub_opts.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<iostream>
#include <windows.h>

using namespace std;

#define sleep Sleep

int MessageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* m);
void onDisconnect(void* context, MQTTAsync_successData* response);
void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onConnect(void* context, MQTTAsync_successData* response);
void onPublishFailure(void* context, MQTTAsync_failureData* response);
void onPublish(void* context, MQTTAsync_successData* response);
void myconnect(MQTTAsync client);
void Create_client(const char* url, MQTTAsync_createOptions* create_opts, MQTTAsync* client);
void Set_Callback();
void Disconnect_Client(MQTTAsync_disconnectOptions disc_opts);
int mypublish(MQTTAsync client, int datalen, string data);
int publish(string s);
int PUBLISHmain();


