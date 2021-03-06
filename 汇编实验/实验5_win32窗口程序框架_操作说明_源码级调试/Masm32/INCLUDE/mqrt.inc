; ..\LIB\MQRT.LIB PROTOTYPES
; ~~~~~~~~~~~~~~~~~~~~~~~~~~

MQBeginTransaction PROTO :DWORD
MQCloseCursor PROTO :DWORD
MQCloseQueue PROTO :DWORD
MQCreateCursor PROTO :DWORD,:DWORD
MQCreateInternalCert PROTO :DWORD
MQCreateQueue PROTO :DWORD,:DWORD,:DWORD,:DWORD
MQDeleteInternalCert PROTO
MQDeleteQueue PROTO :DWORD
MQFreeMemory PROTO :DWORD
MQFreeSecurityContext PROTO :DWORD
MQGetInternalCert PROTO :DWORD
MQGetInternalCertificate PROTO :DWORD,:DWORD,:DWORD
MQGetMachineProperties PROTO :DWORD,:DWORD,:DWORD
MQGetQueueProperties PROTO :DWORD,:DWORD
MQGetQueueSecurity PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MQGetSecurityContext PROTO :DWORD,:DWORD,:DWORD
MQGetUserCerts PROTO :DWORD,:DWORD,:DWORD
MQHandleToFormatName PROTO :DWORD,:DWORD,:DWORD
MQInstanceToFormatName PROTO :DWORD,:DWORD,:DWORD
MQLocateBegin PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MQLocateEnd PROTO :DWORD
MQLocateNext PROTO :DWORD,:DWORD,:DWORD
MQOpenQueue PROTO :DWORD,:DWORD,:DWORD,:DWORD
MQPathNameToFormatName PROTO :DWORD,:DWORD,:DWORD
MQPurgeQueue PROTO :DWORD
MQReceiveMessage PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
MQRegisterUserCert PROTO :DWORD
MQRemoveUserCert PROTO :DWORD
MQSendMessage PROTO :DWORD,:DWORD,:DWORD
MQSetQueueProperties PROTO :DWORD,:DWORD
MQSetQueueSecurity PROTO :DWORD,:DWORD,:DWORD

