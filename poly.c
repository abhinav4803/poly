#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int cof;
  int expo;
  struct Node *Next;
};

// Function to create a new node
struct Node *createNode(int cof, int expo)
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->cof = cof;
  newNode->expo = expo;
  newNode->Next = NULL;
  return newNode;
}

// Insert a term in sorted order and combine like terms
void insertTerm(struct Node **poly, int cof, int expo)
{
  if (cof == 0)
    return; // Skip zero coefficients

  struct Node *temp = *poly, *prev = NULL;

  // Traverse to find the position
  while (temp != NULL && temp->expo > expo)
  {
    prev = temp;
    temp = temp->Next;
  }

  // If same exponent exists, add coefficients
  if (temp != NULL && temp->expo == expo)
  {
    temp->cof += cof;
    if (temp->cof == 0)
    { // Remove zero term
      if (prev)
        prev->Next = temp->Next;
      else
        *poly = temp->Next;
      free(temp);
    }
    return;
  }

  // Create and insert new node
  struct Node *newNode = createNode(cof, expo);
  if (prev == NULL)
  {
    newNode->Next = *poly;
    *poly = newNode;
  }
  else
  {
    newNode->Next = prev->Next;
    prev->Next = newNode;
  }
}

// Print the polynomial
void printPoly(struct Node *poly)
{
  if (!poly)
  {
    printf("0\n");
    return;
  }

  while (poly != NULL)
  {
    printf("%dx^%d", poly->cof, poly->expo);
    poly = poly->Next;
    if (poly != NULL)
      printf(" + ");
  }
  printf("\n");
}

// Add two polynomials
struct Node *addPolynomials(struct Node *poly1, struct Node *poly2)
{
  struct Node *result = NULL;
  while (poly1 != NULL)
  {
    insertTerm(&result, poly1->cof, poly1->expo);
    poly1 = poly1->Next;
  }
  while (poly2 != NULL)
  {
    insertTerm(&result, poly2->cof, poly2->expo);
    poly2 = poly2->Next;
  }
  return result;
}

// Subtract two polynomials
struct Node *subtractPolynomials(struct Node *poly1, struct Node *poly2)
{
  struct Node *result = NULL;
  while (poly1 != NULL)
  {
    insertTerm(&result, poly1->cof, poly1->expo);
    poly1 = poly1->Next;
  }
  while (poly2 != NULL)
  {
    insertTerm(&result, -poly2->cof, poly2->expo);
    poly2 = poly2->Next;
  }
  return result;
}

// Multiply two polynomials
struct Node *multiplyPolynomials(struct Node *poly1, struct Node *poly2)
{
  struct Node *result = NULL;
  struct Node *temp1 = poly1;

  while (temp1 != NULL)
  {
    struct Node *temp2 = poly2;
    while (temp2 != NULL)
    {
      int cof = temp1->cof * temp2->cof;
      int expo = temp1->expo + temp2->expo;
      insertTerm(&result, cof, expo);
      temp2 = temp2->Next;
    }
    temp1 = temp1->Next;
  }
  return result;
}

// Main Function
int main()
{
  struct Node *poly1 = NULL;
  struct Node *poly2 = NULL;

  // Polynomial 1: 3x^2 + 6x^1 + 8
  insertTerm(&poly1, 3, 2);
  insertTerm(&poly1, 6, 1);
  insertTerm(&poly1, 8, 0);

  // Polynomial 2: -3x^1 + 2x^1 = -1x^1
  insertTerm(&poly2, -3, 2);
  insertTerm(&poly2, 2, 1);

  printf("Polynomial 1: ");
  printPoly(poly1);

  printf("Polynomial 2: ");
  printPoly(poly2);

  struct Node *sum = addPolynomials(poly1, poly2);
  printf("Sum: ");
  printPoly(sum);

  struct Node *diff = subtractPolynomials(poly1, poly2);
  printf("Difference (poly1 - poly2): ");
  printPoly(diff);

  struct Node *product = multiplyPolynomials(poly1, poly2);
  printf("Product: ");
  printPoly(product);

  return 0;
}
