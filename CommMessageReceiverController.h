#ifndef _COMM_MESSAGE_RECEIVER_CONTROLLER_H_
#define _COMM_MESSAGE_RECEIVER_CONTROLLER_H_

void initCommMessageReceiverController(void);
int	checkAvailableDataToReceive(void);
char receiveData(void);

#endif
