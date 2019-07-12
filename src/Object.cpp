#include "h/Object.h"
#include "h/Value.h"

Object* Object::m_objects = nullptr;

Object::Object(ObjectType type) : m_type{type} {
    m_next = m_objects;
    m_objects = this;
}

void Object::freeAll() {
    Object* object = m_objects;
    while (object != nullptr) {
        Object* next = object->m_next;
        delete object;
        object = next;
    }
}

bool Object::operator==(const Object &object) const {
    if (m_type != object.m_type) {
        return false;
    }

    switch (m_type) {
        case ObjectType::STRING:
            return this->as<StringObject>()->asStdString() == object.as<StringObject>()->asStdString();
        case ObjectType::ARRAY:
            return this->as<ArrayObject>()->asVector() == object.as<ArrayObject>()->asVector();
    }
}

std::string Object::toString() const {
    if (is<StringObject>()) {
        return as<StringObject>()->asStdString();
    }

    return "";
}

std::ostream& operator<<(std::ostream& stream, const Object& object) {
    stream << object.toString();
    return stream;
}

StringObject::StringObject(std::string data) : Object{ObjectType::STRING}, m_data{std::move(data)} {

}

const std::string &StringObject::asStdString() const {
    return m_data;
}

Type StringObject::getType() const {
    return STRING_TYPE;
}

ArrayObject::ArrayObject() : Object{ObjectType::ARRAY}, m_vector{} {
}

ArrayObject::ArrayObject(std::vector<Value> vector) : Object{ObjectType::ARRAY}, m_vector{std::move(vector)} {
}

std::optional<Value> ArrayObject::at(size_t index) const {
    if (index >= m_vector.size()) {
        return {};
    }

    return {m_vector[index]};
}

const std::vector<Value>& ArrayObject::asVector() const {
    return m_vector;
}

Type ArrayObject::getType() const {
    Type elementType = DYNAMIC_TYPE;

    for (const auto& element : m_vector) {
        elementType = element.getType();
    }

    return std::make_shared<ArrayType>(elementType);
}