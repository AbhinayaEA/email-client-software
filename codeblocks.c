#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMAIL 100
#define MAX_SUBJECT 100
#define MAX_CONTENT 500

// Define the Email structure
typedef struct Email {
    char from[MAX_EMAIL];
    char to[MAX_EMAIL];
    char subject[MAX_SUBJECT];
    char content[MAX_CONTENT];
    struct Email *next;
} Email;

// Queue structure for inbox
typedef struct Queue {
    Email *front, *rear;
} Queue;

// Linked list structure for sent emails
typedef struct LinkedList {
    Email *head;
} LinkedList;

// Function prototypes
int isValidEmail(const char *email);
void enqueue(Queue *q, char *from, char *to, char *subject, char *content);
void dequeue(Queue *q);
void sendEmail(LinkedList *sentList, char *from, char *to, char *subject, char *content);
void displayInbox(Queue *q);
void displaySentEmails(LinkedList *sentList);

// Main function
int main() {
    Queue inbox = {NULL, NULL};
    LinkedList sentEmails = {NULL};

    int choice;
    char from[MAX_EMAIL], to[MAX_EMAIL], subject[MAX_SUBJECT], content[MAX_CONTENT];

    while (1) {
        printf("\n--- Email Management System ---\n");
        printf("1. Receive Email (Add to Inbox)\n");
        printf("2. View Inbox\n");
        printf("3. Send Email\n");
        printf("4. View Sent Emails\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear input buffer

        switch (choice) {
            case 1:
                printf("Enter From Email: ");
                fgets(from, MAX_EMAIL, stdin);
                from[strcspn(from, "\n")] = '\0';
                if (!isValidEmail(from)) {
                    printf("Invalid From Email Address!\n");
                    break;
                }

                printf("Enter To Email: ");
                fgets(to, MAX_EMAIL, stdin);
                to[strcspn(to, "\n")] = '\0';
                if (!isValidEmail(to)) {
                    printf("Invalid To Email Address!\n");
                    break;
                }

                printf("Enter Subject: ");
                fgets(subject, MAX_SUBJECT, stdin);
                subject[strcspn(subject, "\n")] = '\0';

                printf("Enter Content: ");
                fgets(content, MAX_CONTENT, stdin);
                content[strcspn(content, "\n")] = '\0';

                enqueue(&inbox, from, to, subject, content);
                break;

            case 2:
                printf("\n--- Inbox ---\n");
                displayInbox(&inbox);
                break;

            case 3:
                printf("Enter From Email: ");
                fgets(from, MAX_EMAIL, stdin);
                from[strcspn(from, "\n")] = '\0';
                if (!isValidEmail(from)) {
                    printf("Invalid From Email Address!\n");
                    break;
                }

                printf("Enter To Email: ");
                fgets(to, MAX_EMAIL, stdin);
                to[strcspn(to, "\n")] = '\0';
                if (!isValidEmail(to)) {
                    printf("Invalid To Email Address!\n");
                    break;
                }

                printf("Enter Subject: ");
                fgets(subject, MAX_SUBJECT, stdin);
                subject[strcspn(subject, "\n")] = '\0';

                printf("Enter Content: ");
                fgets(content, MAX_CONTENT, stdin);
                content[strcspn(content, "\n")] = '\0';

                sendEmail(&sentEmails, from, to, subject, content);
                break;

            case 4:
                printf("\n--- Sent Emails ---\n");
                displaySentEmails(&sentEmails);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Function to validate email address
int isValidEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    // Check for presence of '@' and '.'
    if (!at || !dot || at > dot)
        return 0;

    // Ensure '@' is not at the beginning and '.' is not at the end
    if (at == email || dot[1] == '\0')
        return 0;

    // Check for invalid characters
    for (const char *p = email; *p; p++) {
        if (!(isalnum(*p) || *p == '@' || *p == '.' || *p == '-' || *p == '_'))
            return 0;
    }

    return 1;
}

// Add email to inbox (Queue)
void enqueue(Queue *q, char *from, char *to, char *subject, char *content) {
    Email *newEmail = (Email *)malloc(sizeof(Email));
    strcpy(newEmail->from, from);
    strcpy(newEmail->to, to);
    strcpy(newEmail->subject, subject);
    strcpy(newEmail->content, content);
    newEmail->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newEmail;
        return;
    }
    q->rear->next = newEmail;
    q->rear = newEmail;
    printf("Email received successfully!\n");
}

// Remove email from inbox (Queue)
void dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Inbox is empty!\n");
        return;
    }

    Email *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    printf("Deleted Email - Subject: %s\n", temp->subject);
    free(temp);
}

// Send email (Add to Sent List)
void sendEmail(LinkedList *sentList, char *from, char *to, char *subject, char *content) {
    Email *newEmail = (Email *)malloc(sizeof(Email));
    strcpy(newEmail->from, from);
    strcpy(newEmail->to, to);
    strcpy(newEmail->subject, subject);
    strcpy(newEmail->content, content);
    newEmail->next = NULL;

    if (sentList->head == NULL) {
        sentList->head = newEmail;
    } else {
        Email *temp = sentList->head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newEmail;
    }
    printf("Email sent successfully!\n");
}

// Display emails in Inbox (Queue)
void displayInbox(Queue *q) {
    if (q->front == NULL) {
        printf("Inbox is empty!\n");
        return;
    }

    Email *temp = q->front;
    while (temp != NULL) {
        printf("From: %s\n", temp->from);
        printf("To: %s\n", temp->to);
        printf("Subject: %s\n", temp->subject);
        printf("Content: %s\n\n", temp->content);
        temp = temp->next;
    }
}

// Display sent emails (Linked List)
void displaySentEmails(LinkedList *sentList) {
    if (sentList->head == NULL) {
        printf("No sent emails!\n");
        return;
    }

    Email *temp = sentList->head;
    while (temp != NULL) {
        printf("From: %s\n", temp->from);
        printf("To: %s\n", temp->to);
        printf("Subject: %s\n", temp->subject);
        printf("Content: %s\n\n", temp->content);
        temp = temp->next;
    }
}
