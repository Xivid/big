/*
 * Direct interrupt delivery
 */
#ifndef _DID_H
#define _DID_H

#define DEVICE_NAME "did"
#define DEVICE "/dev/" DEVICE_NAME

/* Clockevent devices */
typedef struct clockevent_device_t {
        char name[10];
        unsigned int mult;
        unsigned int shift;
} clockevent_device_t;

/* DID */
#define KVM_HC_MAP_PID   9
#define KVM_HC_UNMAP_PID 10
#define KVM_HC_PAGE_WALK 11
#define HYPERCALL_MAP_PID   _IO('k', 9999)
#define HYPERCALL_UNMAP_PID _IO('k', 1000)
#define HYPERCALL_PAGE_WALK _IO('k', 1111)

#define ALLOCATE              _IO('k', 1)
#define DEALLOCATE            _IO('k', 2)
#define SET_EVENT_HANDLER     _IO('k', 3)
#define READ_PIR              _IO('k', 4)
#define WRITE_PIR             _IOW('k',5, unsigned long)
#define TEST_READ             _IO('k', 6)
#define TEST_WRITE            _IO('k', 7)
#define PRINT_DID             _IO('k', 8)
#define RESTORE_EVENT_HANDLER _IO('k', 9)

#define READ_CLOCKEVENT_DEVICES   _IO('k', 28)
#define WRITE_CLOCKEVENT_DEVICES  _IOW('k', 29, clockevent_device_t *)

#define INITIAL_CHAR 'K'

//#define ARRAY_LENGTH(array) (sizeof(array)/sizeof(const char *))
//const char *commands[] = {"allocate", "deallocate", "save_event_handler",
//                           "map", "unmap", "read", "write", "page_walk",
//                           "test_read", "test_write", "print",
//                           "read_clockevent_device",
//                           "write_clockevent_device"};
#endif