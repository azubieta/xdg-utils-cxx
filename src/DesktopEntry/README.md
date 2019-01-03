# Desktop Entry

This module attempts to provide an implementation of the FreeDesktop Desktop 
Entry Specification as is in https://standards.freedesktop.org/desktop-entry-spec/latest/index.html

It is divided in three sections:
 - AST: (stands for Abstract Syntax Tree) provides a data structure to hold the inner representation 
 of the Desktop Entry
 - Reader: provides a parser based on formal grammar production rules which tries 
 to resemble the Desktop Entry format.
 - Public Interface: which is composed by the classes available to the module
 users and abstracts them from all the parsing and formatting rules.
 
 Example usage:
 ```
 using namespace XdgUtils::DesktopEntry;
 ...
 std::ifstream ifs ("miapp.desktop", std::ifstream::in);
 DesktopEntry entry(ifs)
 
 entry.set("Desktop Entry/Name[es]","Mi Gran App");
 
 std::ofstream ofs ("miapp.desktop", std::ofstream::out);
 entry.write(ofs)
 ``` 
 For more usage examples consult the DesktopEntry unit tests.
