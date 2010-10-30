/*
 * Copyright 2006-2008 The FLWOR Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "utf8_chars.h"

namespace zorba {

//
// These words come from http://snowball.tartarus.org/.
//
extern char const *const stop_words_no[] = {
  acirc,
  "alle",
  "at",
  "av",
  "b" acirc "de",
  "b" acirc "e",
  "bare",
  "begge",
  "ble",
  "blei",
  "bli",
  "blir",
  "blitt",
  "da",
  "d" acirc,
  "de",
  "deg",
  "dei",
  "deim",
  "deira",
  "deires",
  "dem",
  "den",
  "denne",
  "der",
  "dere",
  "deres",
  "det",
  "dette",
  "di",
  "din",
  "disse",
  "ditt",
  "du",
  "dykk",
  "dykkar",
  "eg",
  "ein",
  "eit",
  "eitt",
  "eller",
  "elles",
  "en",
  "enn",
  "er",
  "et",
  "ett",
  "etter",
  "for",
  "f" oslash "r",
  "fordi",
  "fra",
  "ha",
  "hadde",
  "han",
  "hans",
  "har",
  "hennar",
  "henne",
  "hennes",
  "her",
  "hj" acirc,
  "ho",
  "hoe",
  "honom",
  "hoss",
  "hossen",
  "hun",
  "hva",
  "hvem",
  "hver",
  "hvilke",
  "hvilken",
  "hvis",
  "hvor",
  "hvordan",
  "hvorfor",
  "i",
  "ikke",
  "ikkje",
  "ikkje",
  "ingen",
  "ingi",
  "inkje",
  "inn",
  "inni",
  "ja",
  "jeg",
  "kan",
  "kom",
  "korleis",
  "korso",
  "kun",
  "kunne",
  "kva",
  "kvar",
  "kvarhelst",
  "kven",
  "kvi",
  "kvifor",
  "man",
  "mange",
  "me",
  "med",
  "medan",
  "meg",
  "meget",
  "mellom",
  "men",
  "mi",
  "min",
  "mine",
  "mitt",
  "mot",
  "mykje",
  "n" acirc,
  "n" acirc "r",
  "ned",
  "no",
  "noe",
  "noen",
  "noka",
  "noko",
  "nokon",
  "nokor",
  "nokre",
  "og",
  "ogs" acirc,
  "om",
  "opp",
  "oss",
  "over",
  "p" acirc,
  "s" acirc,
  "samme",
  "s" acirc "nn",
  "seg",
  "selv",
  "si",
  "si",
  "sia",
  "sidan",
  "siden",
  "sin",
  "sine",
  "sitt",
  "sj" oslash "l",
  "skal",
  "skulle",
  "slik",
  "so",
  "som",
  "som",
  "somme",
  "somt",
  "til",
  "um",
  "upp",
  "ut",
  "uten",
  "var",
  "v" acirc "r",
  "v" aelig "re",
  "v" aelig "re",
  "vart",
  "v" aelig "rt",
  "varte",
  "ved",
  "vere",
  "verte",
  "vi",
  "vil",
  "ville",
  "vore",
  "vors",
  "vort",

  0
};

} // namespace zorba
/* vim:set et sw=2 ts=2: */
