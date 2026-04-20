#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <iomanip>
#include <openssl/sha.h>
#include <cstring>

using namespace std;

// Salt generate karo
string generate_salt(int length) {
    const char* chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string salt;
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> dist(0, strlen(chars) - 1);
    for (int i = 0; i < length; ++i)
        salt += chars[dist(generator)];
    return salt;
}

// Password hash karo
string hash_password(const string& password, const string& salt) {
    string salted = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)salted.c_str(), salted.size(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    return ss.str();
}

int main() {
    string name, email, password;

    cout << "\n===== ADMIN PASSWORD RESET TOOL =====\n";
    cout << "\nAdmin ka naya naam daalo (ya purana: ROBBER): ";
    cin >> name;
    cout << "Admin ki email daalo (ya purani: robber@gmail.com): ";
    cin >> email;
    cout << "Naya password daalo: ";
    cin >> password;

    string salt = generate_salt(16);
    string hashed = hash_password(password, salt);

    // admin_pass.txt overwrite karo
    ofstream write("admin_pass.txt", ios::out | ios::trunc);
    write << name << " " << email << " " << salt << " " << hashed;
    write.close();

    cout << "\n✓ admin_pass.txt update ho gaya!\n";
    cout << "Ab client mein option 3 choose karo aur yeh credentials use karo.\n\n";

    return 0;
}
