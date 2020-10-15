#pragma once
#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"
#include "MQTTAsync.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#define sleep Sleep

using namespace std;

/* External function which are used by subscriber to sava data and keep patient count*/
/*This functions are called upon receiving the patient information*/


int messageArrived(void* context, char* topicName, int topicLen, MQTTAsync_message* message);
void OnDisconnect(void* context, MQTTAsync_successData* response);
void OnSubscribe(void* context, MQTTAsync_successData* response);
void OnSubscribeFailure(void* context, MQTTAsync_failureData* response);
void OnConnectFailure(void* context, MQTTAsync_failureData* response);
void OnConnect(void* context, MQTTAsync_successData* response);
void Create_Client(const char* url, MQTTAsync_createOptions* create_opts, MQTTAsync* client);
void Set_Callback(MQTTAsync client);
void disconnect_Client(MQTTAsync_disconnectOptions disc_opts, MQTTAsync client);
int SUBSCRIBEmain();


