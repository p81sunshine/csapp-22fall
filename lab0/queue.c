/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

#define zero 0

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = zero;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    while (q->head != NULL) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        if (tmp->value != NULL)
            free(tmp->value);
        free(tmp);
    }
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {

    if (q == NULL || s == NULL)
        return false;

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *new_s = malloc((strlen(s) + 1) * sizeof(char));
    if (new_s == NULL) {
        free(newh);
        return false;
    }
    strcpy(new_s, s);

    newh->value = new_s;

    newh->next = q->head;
    q->head = newh;

    /* Handle cases when insert the first element in the queue*/
    if (q->size == 0) {
        q->tail = q->head;
    }

    q->size++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* Remember: It should operate in O(1) time */
    /* When the original size is 0,when should update
     * tail and head both
     */
    if (q == NULL || s == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    char *new_s = malloc((strlen(s) + 1) * sizeof(char));
    if (new_s == NULL) {
        free(newh);
        return false;
    }
    /* Store the value*/
    strcpy(new_s, s);
    newh->value = new_s;
    newh->next = NULL;

    if (q->size > 0) {
        q->tail->next = newh;
        q->tail = newh;
    } else {
        q->tail = newh;
        q->head = q->tail;
    }
    q->size++;

    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {

    /* Head and tail pointer should update simutanously
     * When size of queue > 1 the original implementation is
     * totaly ok.
     * But when the size of queue is 1, that is the tail and
     * the head point to the same memory
     * In this case, we should update both.
     */
    if (q == NULL || q->head == NULL || q->size == zero)
        return false;

    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->head->next;

    if (q->size == 1)
        q->tail = q->head;

    if (buf != NULL) {
        strncpy(buf, tmp->value, bufsize - 1);
        buf[bufsize - 1] = '\0';
    }

    free(tmp->value);

    free(tmp);
    q->size--;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->head == NULL)
        return 0;
    return (size_t)q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */

    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *cur = q->head;
    list_ele_t *next = NULL;
    list_ele_t *pre = NULL;

    q->head = q->tail;
    q->tail = cur;
    while (cur != NULL) {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
}
