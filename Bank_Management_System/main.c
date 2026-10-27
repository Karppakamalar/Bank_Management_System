#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Bank
{
    int account_no;
    char name[30];
    char address[100];
    char mobile[11];
    char email[50];
    char password[20];
    float balance;
};

struct Bank user;


void signup();
void signin();

void name_validation();
void mobile_validation();
void email_validation();
void password_validation();

int generate_account_no();

int verify_login();

void forgot_password();

void deposit();
void withdraw();
void check_balance();
void view_details();
void transaction_history();
void update_file();


int main()
{
    int choice;

    while(1)
    {
        printf("\n========== Bank Management System ==========\n");
        printf("1. Signup\n");
        printf("2. Signin\n");
        printf("3. Exit\n");

        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                signup();
                break;

            case 2:
                signin();
                break;

            case 3:
                printf("Thank You\n");
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }
}

void signup()
{
    FILE *fp;

    printf("\n========== SIGN UP ==========\n");

    printf("Enter Name : ");
    name_validation();

    printf("Enter Address : ");
    scanf(" %[^\n]", user.address);

    printf("Enter Mobile Number : ");
    mobile_validation();

    printf("Enter Email ID : ");
    email_validation();

    printf("Enter Password : ");
    password_validation();

    printf("Enter Initial Balance : ");
    scanf("%f", &user.balance);

    user.account_no = generate_account_no();

    fp = fopen("bank.dat", "ab");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    fwrite(&user, sizeof(user), 1, fp);

    fclose(fp);

    printf("\nAccount Created Successfully.\n");
    printf("Your Account Number : %d\n", user.account_no);
}
void name_validation()
{
    char str[30];

    while(1)
    {
        int i = 0;
        int flag = 0;

        scanf(" %[^\n]", str);

        while(str[i] != '\0')
        {
            if(!isalpha(str[i]) && str[i] != ' ')
            {
                flag = 1;
                break;
            }

            i++;
        }

        if(flag == 0)
        {
            strcpy(user.name, str);
            break;
        }

        printf("Invalid Name. Enter Again : ");
    }
}
void mobile_validation()
{
    char str[11];

    while(1)
    {
        int i = 0;
        int flag = 0;

        scanf("%s", str);

        if(strlen(str) != 10)
        {
            printf("Invalid Mobile Number. Enter Again : ");
            continue;
        }

        while(str[i] != '\0')
        {
            if(!isdigit(str[i]))
            {
                flag = 1;
                break;
            }

            i++;
        }

        if(flag == 0)
        {
            strcpy(user.mobile, str);
            break;
        }

        printf("Invalid Mobile Number. Enter Again : ");
    }
}
void email_validation()
{
    char str[50];

    while(1)
    {
        int flag = 0;

        scanf("%s", str);

        int n = strlen(str);

        if(n <= 10)
        {
            flag = 1;
        }

        else if(strcmp(str + n - 10, "@gmail.com") != 0)
        {
            flag = 1;
        }

        else
        {
            for(int i = 0; i < n - 10; i++)
            {
                if(!islower(str[i]) && !isdigit(str[i]))
                {
                    flag = 1;
                    break;
                }
            }
        }

        if(flag == 0)
        {
            strcpy(user.email, str);
            break;
        }

        printf("Invalid Email ID. Enter Again : ");
    }
}
void password_validation()
{
    char str[20];
    char confirm[20];

    while(1)
    {
        int i = 0;
        int upper = 0;
        int special = 0;

        scanf("%s", str);

        if(strlen(str) < 6)
        {
            printf("Password must contain minimum 6 characters.\n");
            printf("Enter Password Again : ");
            continue;
        }

        while(str[i] != '\0')
        {
            if(isupper(str[i]))
                upper = 1;

            if(!isalnum(str[i]))
                special = 1;

            i++;
        }

        if(upper == 0)
        {
            printf("Password must contain at least one uppercase letter.\n");
            printf("Enter Password Again : ");
            continue;
        }

        if(special == 0)
        {
            printf("Password must contain at least one special character.\n");
            printf("Enter Password Again : ");
            continue;
        }

        printf("Confirm Password : ");
        scanf("%s", confirm);

        if(strcmp(str, confirm) != 0)
        {
            printf("Passwords do not match.\n");
            printf("Enter Password Again : ");
            continue;
        }

        strcpy(user.password, str);
        break;
    }
}
int generate_account_no()
{
    FILE *fp;
    struct Bank temp;
    int acc = 1000;

    fp = fopen("bank.dat", "rb");

    if(fp == NULL)
        return 1001;

    while(fread(&temp, sizeof(struct Bank), 1, fp))
    {
        acc = temp.account_no;
    }

    fclose(fp);

    return acc + 1;
}
int verify_login()
{
    FILE *fp;
    int account_no;
    char password[20];

    fp = fopen("bank.dat","rb");

    if(fp == NULL)
    {
        printf("No Account Found.\n");
        return 0;
    }

    printf("Enter Account Number : ");
    scanf("%d",&account_no);

    printf("Enter Password : ");
    scanf("%s",password);

    while(fread(&user,sizeof(struct Bank),1,fp))
    {
        if(user.account_no == account_no &&
           strcmp(user.password,password) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
void signin()
{
    int choice;

    while(1)
    {
        printf("\n========== SIGN IN ==========\n");
        printf("1. Login\n");
        printf("2. Forgot Password\n");
        printf("3. Back\n");

        printf("Enter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:

                if(verify_login())
                {
                    printf("\nLogin Successful.\n");

                    while(1)
                    {
                        printf("\n========== BANK MENU ==========\n");
                        printf("1. Deposit\n");
                        printf("2. Withdraw\n");
                        printf("3. Check Balance\n");
                        printf("4. View Details\n");
                        printf("5. Transaction History\n");
                        printf("6. Logout\n");

                        printf("Enter Choice : ");
                        scanf("%d",&choice);

                        switch(choice)
                        {
                            case 1:
                                deposit();
                                break;

                            case 2:
                                withdraw();
                                break;

                            case 3:
                                check_balance();
                                break;

                            case 4:
                                view_details();
                                break;

                            case 5:
                                transaction_history();
                                break;
                            case 6:
                                return;

                            default:
                                printf("Invalid Choice\n");
                        }
                    }
                }
                else
                {
                    printf("Invalid Account Number or Password\n");
                }

                break;

            case 2:
                forgot_password();
                break;

            case 3:
                return;

            default:
                printf("Invalid Choice\n");
        }
    }
}
void forgot_password()
{
    FILE *fp;
    FILE *temp;

    int account_no;
    char email[50];

    fp = fopen("bank.dat","rb");
    temp = fopen("temp.dat","wb");

    if(fp == NULL)
    {
        printf("No Account Found.\n");
        return;
    }

    printf("Enter Account Number : ");
    scanf("%d",&account_no);

    printf("Enter Registered Email : ");
    scanf("%s",email);

    int found = 0;

    while(fread(&user,sizeof(struct Bank),1,fp))
    {
        if(user.account_no == account_no &&
           strcmp(user.email,email) == 0)
        {
            printf("Enter New Password : ");
            password_validation();

            found = 1;
        }

        fwrite(&user,sizeof(struct Bank),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.dat");
    rename("temp.dat","bank.dat");

    if(found)
        printf("Password Changed Successfully.\n");
    else
        printf("Invalid Account Number or Email.\n");
}
void deposit()
{
    FILE *fp;
    FILE *temp;

    struct Bank temp_user;

    float amount;

    printf("Enter Amount to Deposit : ");
    scanf("%f",&amount);

    if(amount <= 0)
    {
        printf("Invalid Amount.\n");
        return;
    }

    fp = fopen("bank.dat","rb");
    temp = fopen("temp.dat","wb");

    while(fread(&temp_user,sizeof(struct Bank),1,fp))
    {
        if(temp_user.account_no == user.account_no)
        {
            temp_user.balance += amount;

            user = temp_user;

            printf("Amount Deposited Successfully.\n");
            FILE *history;
            history = fopen("transaction.txt","a");
            fprintf(history,"%d Deposit %.2f Balance %.2f\n",user.account_no,amount,user.balance);
            fclose(history);
        }

        fwrite(&temp_user,sizeof(struct Bank),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.dat");
    rename("temp.dat","bank.dat");
}
void withdraw()
{
    FILE *fp;
    FILE *temp;

    struct Bank temp_user;

    float amount;

    printf("Enter Amount to Withdraw : ");
    scanf("%f",&amount);

    if(amount <= 0)
    {
        printf("Invalid Amount.\n");
        return;
    }

    fp = fopen("bank.dat","rb");
    temp = fopen("temp.dat","wb");

    while(fread(&temp_user,sizeof(struct Bank),1,fp))
    {
        if(temp_user.account_no == user.account_no)
        {
            if(amount > temp_user.balance)
            {
                printf("Insufficient Balance.\n");
            }
            else
            {
                temp_user.balance -= amount;

                user = temp_user;

                printf("Amount Withdrawn Successfully.\n");
                FILE *history;
                history = fopen("transaction.txt","a");
                fprintf(history,"%d Withdraw %.2f Balance %.2f\n",user.account_no,amount,user.balance);
                fclose(history);
            }
        }

        fwrite(&temp_user,sizeof(struct Bank),1,temp);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.dat");
    rename("temp.dat","bank.dat");

}

void check_balance()
{
    printf("\n========== BALANCE ==========\n");
    printf("Current Balance : %.2f\n",user.balance);

}

void view_details()
{
    
    printf("\n========== ACCOUNT DETAILS ==========\n");

    printf("Account Number : %d\n",user.account_no);
    printf("Name           : %s\n",user.name);
    printf("Address        : %s\n",user.address);
    printf("Mobile Number  : %s\n",user.mobile);
    printf("Email ID       : %s\n",user.email);
    printf("Balance        : %.2f\n",user.balance);

}
void transaction_history()
{
    FILE *fp;

    int account_no;
    char type[20];
    float amount;
    float balance;

    fp = fopen("transaction.txt","r");

    if(fp == NULL)
    {
        printf("No Transaction History Found.\n");
        return;
    }

    printf("\n========== TRANSACTION HISTORY ==========\n");

    while(fscanf(fp,"%d %s %f %*s %f",
                 &account_no,
                 type,
                 &amount,
                 &balance) != EOF)
    {
        if(account_no == user.account_no)
        {
            printf("\n%s : %.2f",type,amount);
            printf("\nBalance : %.2f\n",balance);
        }
    }

    fclose(fp);
}
void update_file()
{

}