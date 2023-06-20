//
// Created by fox on 2023/6/20.
//

#ifndef MY_CONFIG_H
#define MY_CONFIG_H

#include <memory>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <utility>
#include "log.h"

namespace sylar {

    class ConfigVarBase {
    public:
        using ptr = std::shared_ptr<ConfigVarBase>;

        explicit ConfigVarBase(std::string name, std::string description = "");

        virtual ~ConfigVarBase() = default;

        const std::string &getMName() const;

        const std::string &getMDescription() const;

        virtual std::string toString() = 0;

        virtual bool fromString(const std::string &val) = 0;

    protected:
        std::string m_name;
        std::string m_description;
    };

    ConfigVarBase::ConfigVarBase(std::string name, std::string description) : m_name(std::move(name)),
                                                                              m_description(std::move(description)) {

    }

    const std::string &ConfigVarBase::getMName() const {
        return m_name;
    }

    const std::string &ConfigVarBase::getMDescription() const {
        return m_description;
    }

    template<class T>
    class ConfigVar : public ConfigVarBase {
    public:
        using ptr = std::shared_ptr<ConfigVar>;

        ConfigVar(const std::string &name, T mVal, const std::string &description = "") : ConfigVarBase(name,
                                                                                                        description),
                                                                                          m_val(mVal) {}

        std::string toString() override {
            try {
                boost::lexical_cast<std::string>(m_val);
            } catch (std::exception &e) {
                SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception" << e.what() << " convert: "
                                                  << typeid(m_val).name() << " to string";
            }
            return {};
        }

        bool fromString(const std::string &val) override {
            try {
                m_val = boost::lexical_cast<T>(val);
            } catch (std::exception &e) {
                SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception" << e.what()
                                                  << " convert: string to"
                                                  << typeid(m_val).name();
            }
            return false;
        }

        ~ConfigVar() override = default;

    private:
        T m_val;

    };

    class Config{
    public:
        using ConfigVarMap = std::map<std::string, ConfigVarBase::ptr>;

        template<class T> static typename ConfigVar<T>::ptr Lookup(const std::string &name, T mVal, const std::string &description = ""){
            auto tmp = Lookup<T>(name);
            if(tmp){
                SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name = " <<name<<" exists";
                return tmp;
            }
            if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ._0123456789")!=std::string::npos){
                SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) <<"Lookup name Invalid "<<name;
                throw std::invalid_argument(name);
            }
            typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, mVal,description));
            s_datas[name] = v;
        }
        template<class T> static typename ConfigVar<T>::ptr Lookup(const std::string &name){
            auto it = s_datas.find(name);
            if(it == s_datas.end()){
                return nullptr;
            }
            return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
        }
    private:
        static ConfigVarMap s_datas;
    };


}

#endif //MY_CONFIG_H
