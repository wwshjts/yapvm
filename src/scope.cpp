#include "scope.h"

using namespace yapvm::interpreter;


Scope::Scope() : parent_{ nullptr } {
    scope_.add(lst_exec_res, ScopeEntry{ nullptr, OBJECT });
}


bool Scope::add_object(std::string name, ManagedObject *value) {
    assert(value != nullptr);
    return scope_.add(std::move(name), ScopeEntry{static_cast<void *>(value), OBJECT});
}

bool Scope::add_function(std::string signature, FunctionDef *function) {
    assert(function != nullptr);
    return scope_.add(std::move(signature), ScopeEntry{static_cast<void *>(function), FUNCTION});
}

bool Scope::add_child_scope(std::string name, Scope *subscope) {
    assert(subscope != nullptr);
    subscope->parent_ = this;
    return scope_.add(std::move(name), ScopeEntry{static_cast<void *>(subscope), SCOPE});
}

bool Scope::add(std::string name, ScopeEntry entry) { return scope_.add(std::move(name), entry); }


void Scope::change(const std::string &name, ScopeEntry new_entry) {
    std::optional<std::reference_wrapper<ScopeEntry>> opt_from_kv = scope_[name];
    if (!opt_from_kv.has_value()) {
        add(name, new_entry);
        return;
    }

    ScopeEntry &entry = opt_from_kv.value().get();
    entry = new_entry;
}

void Scope::store_last_exec_res(const std::string &name) {
    change(name, get(lst_exec_res).value());
}


ManagedObject *Scope::get_object(const std::string &name) {
    std::optional<std::reference_wrapper<ScopeEntry>> opt_from_kv = scope_[name];
    if (opt_from_kv == std::nullopt) return nullptr; 
    ScopeEntry se_ref = opt_from_kv.value().get();
    return static_cast<ManagedObject *>(se_ref.value_);
}

FunctionDef *Scope::get_function(const std::string &signature) {
    std::optional<std::reference_wrapper<ScopeEntry>> opt_from_kv = scope_[signature];
    if (opt_from_kv == std::nullopt) return nullptr; 
    ScopeEntry se_ref = opt_from_kv.value().get();
    return static_cast<FunctionDef *>(se_ref.value_);   
}

std::optional<ScopeEntry> Scope::get(const std::string &name) {
    std::optional<std::reference_wrapper<ScopeEntry>> opt_from_kv = scope_[name];
    if (opt_from_kv == std::nullopt) return std::nullopt; 
    ScopeEntry se_ref = opt_from_kv.value().get();
    return std::optional<ScopeEntry>{ se_ref };
}

std::vector<Scope *> Scope::get_all_children() const {
    std::vector<Scope *> children;
    for (std::vector<ScopeEntry *> fields = scope_.get_live_entries_values(); ScopeEntry *f : fields) {
        if (f->type_ == SCOPE) children.push_back(static_cast<Scope *>(f->value_));
    }
    return children;
}

Scope* Scope::parent() const {
    return parent_;
}