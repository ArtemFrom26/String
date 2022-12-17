#include <iostream>
#include <cstring>

size_t find_size(const size_t num) {
  size_t answer = 1;
  while (answer < num)
    answer = answer << 1;

  return answer;
}

class String {
 private:
  size_t len;
  size_t smb_am;
  char* str;

  void resize(size_t length) {
    if (len > length)
      return;

    length = find_size(length);
    char* temp_str = new char[length];
    memcpy(temp_str, str, smb_am);
    delete[] str;
    len = length;
    str = temp_str;
  }

  bool check_substr(const size_t first, const size_t count, const String& substr) const {
    for (size_t i = 0; i < count; ++i) {
      if (str[first + i] != substr[i])
        return false;
    }
    return true;
  }

 public:
  String(const char* s) {
    smb_am = strlen(s);
    len = find_size(smb_am);
    str = new char[len];
    memcpy(str, s, smb_am);
  }

  String(const int n, char c) {
    smb_am = n;
    len = find_size(smb_am);
    str = new char[len];
    memset(str, c, smb_am);
  }

  String() {
    len = 0;
    smb_am = 0;
    str = nullptr;
  }

  String(const String& s) {
    len = s.len;
    smb_am = s.smb_am;
    str = new char[len];
    memcpy(str, s.str, smb_am);
  }

  String& operator= (const String s) {
    len = s.len;
    smb_am = s.smb_am;
    str = new char[len];
    memcpy(str, s.str, smb_am);
    return *this;
  }

  ~String() {
    delete[] str;
    str = nullptr;
  }

  String(char c) {
    smb_am = 1;
    len = 2;
    str = new char[len];
    str[0] = c;
  }

  const char& operator[] (const size_t index) const {
    return str[index];
  }

  char& operator[] (const size_t index) {
    return str[index];
  }

  size_t length() const {
    return smb_am;
  }

  void push_back(const char c) {
    if (len == smb_am)
      resize(len + 1);

    str[smb_am] = c;
    ++smb_am;
  }

  void pop_back() {
    --smb_am;
  }

  const char& front() const {
    return str[0];
  }

  char& front() {
    return str[0];
  }

  const char& back() const {
    return str[smb_am - 1];
  }

  char& back() {
    return str[smb_am - 1];
  }

  String& operator+= (const String& s) {
    resize(smb_am + s.length());
    memcpy(str + smb_am, s.str, s.length());
    smb_am += s.length();
    return *this;
  }

  size_t find(const String& substring) const {
    for (size_t i = 0; i + substring.length() <= smb_am; ++i) {
      if (check_substr(i, substring.length(), substring))
        return i;
    }
    return smb_am;
  }

  size_t rfind(const String& substring) const {
    size_t i = smb_am - substring.length();
    do {
      if (check_substr(i, substring.length(), substring))
        return i;
      --i;
    } while (i != 0);
    return len;
  }

  String substr(const size_t first, const size_t count) const {
    String temp;
    temp.resize(count);
    temp.smb_am = count;

    for (size_t i = 0; i < count; ++i)
      temp.str[i] = str[first + i];

    return temp;
  }

  bool empty() const{
    return smb_am == 0;
  }

  void clear() {
    len = 0;
    smb_am = 0;
    delete[] str;
    str = nullptr;
  }
};

bool operator== (const String& a, const String& b) {
  if (a.length() != b.length())
    return false;

  for (size_t i = 0; i < a.length(); ++i) {
    if (a[i] != b[i])
      return false;
  }

  return true;
}

String operator+ (const String& left, const String& right) {
  String res(left);
  res += right;
  return res;
}

std::ostream& operator<< (std::ostream& out, const String& s) {
  for (size_t i = 0; i < s.length(); ++i) {
    out << s[i];
  }
  return out;
}

std::istream& operator>> (std::istream& in, String& str) {
  char c;
  str.clear();
  do {
    c = in.get();
  } while (isspace(c));
  while (!in.eof() && !isspace(c)) {
    str.push_back(c);
    c = in.get();
  }
  return in;
}
