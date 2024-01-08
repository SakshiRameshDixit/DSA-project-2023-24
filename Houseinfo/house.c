#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Structure to represent a house
struct House {
    int slumNo;
    int houseNo;
    int numOfMembers;
    char houseName[50];
    struct House* left;
    struct House* right;
};

// Function to create a new house node
struct House* createHouse(int slumNo, int houseNo, int numOfMembers, const char* houseName) {
    struct House* newHouse = (struct House*)malloc(sizeof(struct House));
    newHouse->slumNo = slumNo;
    newHouse->houseNo = houseNo;
    newHouse->numOfMembers = numOfMembers;
    strcpy(newHouse->houseName, houseName);
    newHouse->left = NULL;
    newHouse->right = NULL;
    return newHouse;
}

// Function to insert a new house into the BST
struct House* insert(struct House* root, int slumNo, int houseNo, int numOfMembers, const char* houseName) {
    if (root == NULL) {
        return createHouse(slumNo, houseNo, numOfMembers, houseName);
    }

    if (houseNo < root->houseNo) {
        root->left = insert(root->left, slumNo, houseNo, numOfMembers, houseName);
    } else if (houseNo > root->houseNo) {
        root->right = insert(root->right, slumNo, houseNo, numOfMembers, houseName);
    }

    return root;
}

// Function to perform an in-order traversal and display houses of a specific slum
void displayHousesInSlum(struct House* root, int slumNo) {
    if (root != NULL) {
        displayHousesInSlum(root->left, slumNo);

        if (root->slumNo == slumNo) {
            printf("Slum No: %d, House No: %d, Members: %d, Name: %s\n", root->slumNo, root->houseNo, root->numOfMembers, root->houseName);
        }

        displayHousesInSlum(root->right, slumNo);
    }
}

// Function to free the memory allocated for the BST
void freeBST(struct House* root) {
    if (root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

int main() {
    struct House* root = NULL;

    // Inserting houses into the BST
    FILE * fp = fopen("houses.txt", "r");

    while(!feof(fp)){
        int slumNo, houseNo, numOfMembers;
        char houseName[50];
        fscanf(fp, "%d %d %d %s",&slumNo, &houseNo, &numOfMembers, houseName);
        root = insert(root, slumNo, houseNo, numOfMembers, houseName);
    }
    fclose(fp);
   

    // Displaying houses in Slum No 5
    printf("Houses in Slum No 5:\n");
    displayHousesInSlum(root, 5);

    // Freeing the memory
    freeBST(root);

    return 0;
}
