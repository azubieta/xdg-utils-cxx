// libraries
#include <gtest/gtest.h>

// local
#include <XdgUtils/DesktopEntry/DesktopEntryKeyValue.h>
#include "DesktopEntryKeyValuePriv.h"
#include <AST/Entry.h>

using namespace XdgUtils::DesktopEntry;

class FakeDesktopEntryKeyValue : public DesktopEntryKeyValue {
public:
    FakeDesktopEntryKeyValue(const DesktopEntryKeyPath& path, const std::shared_ptr<AST::Node>& node) :
        DesktopEntryKeyValue(new DesktopEntryKeyValue::Priv(path, node)) {
    }
};

TEST(TestDesktopEntryKeyValue, cstringCasting) {
    DesktopEntryKeyPath path("Group/Entry");
    auto astNode = std::make_shared<AST::Entry>("Entry", "", "value");


    FakeDesktopEntryKeyValue valueImpl(path, astNode);
    DesktopEntryKeyValue& value = valueImpl;

    ASSERT_STREQ(static_cast<const char*>(value), "value");

    value = "rock";
    ASSERT_STREQ(static_cast<const char*>(value), "rock");
}

TEST(TestDesktopEntryKeyValue, stringCasting) {
    DesktopEntryKeyPath path("Group/Entry");
    auto astNode = std::make_shared<AST::Entry>("Entry", "", "value");


    FakeDesktopEntryKeyValue valueImpl(path, astNode);
    DesktopEntryKeyValue& value = valueImpl;

    ASSERT_EQ(static_cast<std::string>(value), "value");

    value = std::string("rock");
    ASSERT_EQ(static_cast<std::string>(value), "rock");
}

TEST(TestDesktopEntryKeyValue, boolCasting) {
    DesktopEntryKeyPath path("Group/Entry");
    auto astNode = std::make_shared<AST::Entry>("Entry", "", "true");

    FakeDesktopEntryKeyValue valueImpl(path, astNode);
    DesktopEntryKeyValue& value = valueImpl;

    ASSERT_TRUE(static_cast<bool>(value));

    value = false;
    ASSERT_FALSE(static_cast<bool>(value));

    value = true;
    ASSERT_TRUE(static_cast<bool>(value));

    value = std::string(" True ");
    ASSERT_TRUE(static_cast<bool>(value));

    value = std::string("    TRUE");
    ASSERT_TRUE(static_cast<bool>(value));

    value = std::string("false");
    ASSERT_FALSE(static_cast<bool>(value));

    value = std::string("FaLsE ");
    ASSERT_FALSE(static_cast<bool>(value));

    value = std::string("  fAlse");
    ASSERT_FALSE(static_cast<bool>(value));
}

TEST(TestDesktopEntryKeyValue, badBoolCasting) {
    DesktopEntryKeyPath path("Group/Entry");
    auto astNode = std::make_shared<AST::Entry>("Entry", "", "not a bool");

    FakeDesktopEntryKeyValue valueImpl(path, astNode);
    DesktopEntryKeyValue& value = valueImpl;

    ASSERT_THROW(static_cast<bool>(value), XdgUtils::DesktopEntry::BadCast);
}

TEST(TestDesktopEntryKeyValue, intCasting) {
    FakeDesktopEntryKeyValue valueImpl(DesktopEntryKeyPath("Group/Entry"),
                                       std::make_shared<AST::Entry>("Entry", "", "123"));

    DesktopEntryKeyValue& value = valueImpl;

    ASSERT_EQ(static_cast<int>(value), 123);

    value = 44;
    ASSERT_EQ(static_cast<int>(value), 44);
}

TEST(TestDesktopEntryKeyValue, doubleCasting) {
    FakeDesktopEntryKeyValue valueImpl(DesktopEntryKeyPath("Group/Entry"),
                                       std::make_shared<AST::Entry>("Entry", "", "1.2"));

    DesktopEntryKeyValue& value = valueImpl;

    ASSERT_EQ(static_cast<double>(value), 1.2);

    value = 3.2;
    ASSERT_EQ(static_cast<double>(value), 3.2);
}


TEST(TestDesktopEntryKeyValue, copy) {
    FakeDesktopEntryKeyValue valueImpl1(DesktopEntryKeyPath("Group/Entry"),
                                        std::make_shared<AST::Entry>("Entry", "", "1.2"));

    DesktopEntryKeyValue& value1 = valueImpl1;


    FakeDesktopEntryKeyValue valueImpl2(DesktopEntryKeyPath("Group/Entry"),
                                        std::make_shared<AST::Entry>("Entry", "", "1.4"));

    DesktopEntryKeyValue& value2 = valueImpl2;

    ASSERT_EQ(static_cast<std::string>(value1), "1.2");
    ASSERT_EQ(static_cast<std::string>(value2), "1.4");

    value1 = value2;
    ASSERT_EQ(static_cast<std::string>(value1), "1.4");
}
