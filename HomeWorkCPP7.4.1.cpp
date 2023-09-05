#include <iostream>
#include <fstream>

class PrintableAsHTML {

public:

    virtual ~PrintableAsHTML() = default;

private:

    virtual std::string printAsHTML() const = 0;
};

class PrintableAsText {

public:

    virtual ~PrintableAsText() = default;

private:

    virtual std::string printAsText() const = 0;
};

class PrintableAsJSON {

public:

    virtual ~PrintableAsJSON() = default;

private:

    virtual std::string printAsJSON() const = 0;
};

class Data : public PrintableAsHTML, public PrintableAsText, public PrintableAsJSON {

public:

    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data) : data_(std::move(data)) {}

    std::string printable(Format format) const {

        if (format == Format::kHTML) {

            return printAsHTML();
        }
        else if (format == Format::kText) {

            return printAsText();
        }
        else if (format == Format::kJSON) {

            return printAsJSON();
        }
        else {

            throw std::runtime_error("Invalid format!");
        }
    }

private:

    std::string data_;

    std::string printAsHTML() const override {

        return "<html>" + data_ + "<html/>";
    }

    std::string printAsText() const override {

        return data_;
    }

    std::string printAsJSON() const override {

        return "{ \"data\": \"" + data_ + "\"}";
    }
};



void saveTo(std::ofstream& out, const Data& data, Data::Format format) {

    out << data.printable(format);
}

void saveToAsHTML(std::ofstream& out, const Data& data) {

    saveTo(out, data, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream& out, const Data& data) {

    saveTo(out, data, Data::Format::kJSON);
}

void saveToAsText(std::ofstream& out, const Data& data) {

    saveTo(out, data, Data::Format::kText);
}



int main() {

    std::ofstream file("out.txt", std::ios::app);
    std::string messing("Hello World!");

    Data data(messing);

    saveToAsHTML(file, data);
    saveToAsJSON(file, data);
    saveToAsText(file, data);
}