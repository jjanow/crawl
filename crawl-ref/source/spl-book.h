/**
 * @file
 * @brief Spellbook contents array and management functions
**/

#pragma once

#include <vector>

#define RANDBOOK_SIZE 8
#include "item-prop-enum.h"
#include "menu.h"
#include "spl-util.h" // spschool

using std::vector;

#define SPELL_LIST_KEY "spell_list"

/// Should the book's name NOT use articles? (Foo's Bar of Baz, not the Foo's)
#define BOOK_TITLED_KEY "is_named"

class formatted_string;

struct sortable_spell
{
    sortable_spell(spell_type s);

    spell_type spell;
    int raw_fail;
    int fail_rate;
    int fail_rate_colour;
    int level;
    int difficulty;
    string name;
    string school; // TODO: set?

    friend bool operator==(const sortable_spell& x, const sortable_spell& y)
    {
        return x.spell == y.spell;
    }
};

struct hash_sortable_spell
{
    spell_type operator()(const sortable_spell& s) const
    {
        return s.spell;
    }
};

typedef vector<sortable_spell>                 spell_lib_list;
typedef unordered_set<spell_type, hash<int>>   spell_set;

class SpellLibraryMenu : public Menu
{
public:
    enum class action { cast, memorise, imbue, describe, hide, unhide };
    action current_action, default_action;

    SpellLibraryMenu(spell_lib_list& list, action _default_action, bool use_spell_letters = false);

protected:
    virtual formatted_string calc_title() override;
    virtual string get_keyhelp(bool) const override;
    virtual bool cycle_mode(bool forward) override;
    command_type get_command(int keyin) override;
    virtual bool process_command(command_type cmd) override;

    colour_t entry_colour(const sortable_spell& entry);
    void update_entries();

private:
    spell_lib_list& spells;
    string spell_levels_str;
    string search_text;
    int hidden_count;
    bool use_spell_letters;
};

bool book_exists(book_type which_book);
#ifdef DEBUG
void validate_spellbooks();
#endif
bool is_player_spell(spell_type which_spell);
bool is_player_book_spell(spell_type which_spell);
bool is_wand_spell(spell_type spell);

bool book_has_title(const item_def &book);

bool can_learn_spell(bool silent = false);
bool player_has_available_spells();
bool learn_spell();
bool learn_spell(spell_type spell, bool wizard = false, bool interactive = true);

bool library_add_spells(vector<spell_type> spells, bool quiet = false);

string desc_cannot_memorise_reason(spell_type spell);

spell_type spell_in_wand(wand_type wand);
vector<spell_type> spellbook_template(book_type book);
vector<spell_type> spells_in_book(const item_def &book);

bool you_can_memorise(spell_type spell) PURE;
bool has_spells_to_memorise(bool silent = true);
vector<spell_type> get_sorted_spell_list(bool silent = false,
                                         bool memorise_only = true);
spell_lib_list get_available_spell_list(bool silent = false,
                                    bool memorise_only = true);
bool sort_mem_spells(const sortable_spell &a, const sortable_spell &b);
bool sort_divine_spells(const sortable_spell &a, const sortable_spell &b);
spret divine_exegesis(bool fail);

spret imbue_servitor();

book_type choose_book_type(int item_level);
