#include <memory>
#include <vector>
#include <sstream>
#include <iostream>


class Book
{
public:
    Book(std::string name, std::string author) : _name(std::move(name)), _author(std::move(author)) {}

    std::string to_string()
    {
        std::stringstream ss;
        ss << "name: " << _name << ", author: " << _author;
        return ss.str();
    }

private:
    std::string _name;
    std::string _author;
};

class BookShelf
{
public:
    BookShelf() = default;

    /// 向书架放入一本书
    void book_insert(const std::shared_ptr<Book> &book) { _book_list.push_back(book); }

    std::string to_string()
    {
        std::stringstream ss;
        for (const auto &book: _book_list)
        {
            ss << book->to_string() << "\n";
        }
        return ss.str();
    }

private:
    std::vector<std::shared_ptr<Book>> _book_list;
};


int main()
{

    auto                  book_lick_your_mouth = std::make_shared<Book>("舔嘴秘方", "???");
    std::shared_ptr<Book> book_pig;
    {
        auto ptr = new Book("母猪的产后护理", "123");
        book_pig = std::shared_ptr<Book>(ptr);
    }

    BookShelf book_shelf;
    book_shelf.book_insert(book_lick_your_mouth);
    book_shelf.book_insert(book_pig);

    std::cout << book_shelf.to_string() << std::endl;
}