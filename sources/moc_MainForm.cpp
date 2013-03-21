/****************************************************************************
** Meta object code from reading C++ file 'MainForm.h'
**
** Created: Mon 23. May 18:54:17 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainForm[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      37,    9,    9,    9, 0x08,
      60,    9,    9,    9, 0x08,
      79,    9,    9,    9, 0x08,
      91,    9,    9,    9, 0x08,
     107,    9,    9,    9, 0x08,
     120,    9,    9,    9, 0x08,
     140,    9,    9,    9, 0x08,
     163,    9,    9,    9, 0x08,
     191,    9,    9,    9, 0x08,
     225,  210,    9,    9, 0x08,
     257,    9,    9,    9, 0x08,
     286,    9,    9,    9, 0x08,
     309,    9,    9,    9, 0x08,
     336,  322,    9,    9, 0x08,
     367,    9,    9,    9, 0x28,
     394,    9,    9,    9, 0x08,
     412,    9,    9,    9, 0x08,
     422,    9,    9,    9, 0x08,
     435,    9,    9,    9, 0x08,
     455,    9,    9,    9, 0x08,
     482,    9,    9,    9, 0x08,
     501,    9,    9,    9, 0x08,
     523,    9,    9,    9, 0x08,
     548,    9,    9,    9, 0x08,
     566,    9,    9,    9, 0x08,
     591,    9,    9,    9, 0x08,
     614,    9,    9,    9, 0x08,
     634,    9,    9,    9, 0x08,
     654,    9,    9,    9, 0x08,
     676,    9,    9,    9, 0x08,
     697,    9,    9,    9, 0x08,
     718,    9,    9,    9, 0x08,
     752,  742,    9,    9, 0x08,
     783,    9,    9,    9, 0x08,
     804,    9,    9,    9, 0x08,
     825,    9,    9,    9, 0x08,
     845,    9,    9,    9, 0x08,
     876,    9,    9,    9, 0x08,
     897,    9,    9,    9, 0x08,
     917,    9,    9,    9, 0x08,
     938,    9,    9,    9, 0x08,
     959,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainForm[] = {
    "MainForm\0\0closeAddIngredientDialog()\0"
    "openAddNewIngredient()\0openAddNewRecipe()\0"
    "openAbout()\0openReporting()\0closeAbout()\0"
    "chooseImageRecipe()\0closeAddRecipeDialog()\0"
    "openAssocIngrRecipeDialog()\0"
    "addNewIngredient()\0ingredientName\0"
    "getUnitsFromIngredient(QString)\0"
    "closeAssocIngrRecipeDialog()\0"
    "applyIngrRecipeAssoc()\0removeIngr()\0"
    "manualCommand\0checkBoxNoUnitIngredient(bool)\0"
    "checkBoxNoUnitIngredient()\0openAddCookStep()\0"
    "addUnit()\0removeUnit()\0openManageUnities()\0"
    "closeManageUnitiesDialog()\0"
    "addNewUnitMethod()\0removeOldUnitMethod()\0"
    "removeAllUnitiesMethod()\0openAddMaterial()\0"
    "closeAddMaterialDialog()\0"
    "removeActionMaterial()\0addActionMaterial()\0"
    "openManageActions()\0getSelectedMaterial()\0"
    "closeManageActions()\0addActionMaterial2()\0"
    "removeActionMaterial2()\0actionKey\0"
    "toggleActionToMaterial2(short)\0"
    "applyManageActions()\0addNewActionMethod()\0"
    "addMaterialMethod()\0getMaterialFromActionRefresh()\0"
    "closeAddStepDialog()\0addCookStepMethod()\0"
    "removeStepToRecipe()\0submitRecipeMethod()\0"
    "openRecipe()\0"
};

const QMetaObject MainForm::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainForm,
      qt_meta_data_MainForm, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainForm))
        return static_cast<void*>(const_cast< MainForm*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeAddIngredientDialog(); break;
        case 1: openAddNewIngredient(); break;
        case 2: openAddNewRecipe(); break;
        case 3: openAbout(); break;
        case 4: openReporting(); break;
        case 5: closeAbout(); break;
        case 6: chooseImageRecipe(); break;
        case 7: closeAddRecipeDialog(); break;
        case 8: openAssocIngrRecipeDialog(); break;
        case 9: addNewIngredient(); break;
        case 10: getUnitsFromIngredient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: closeAssocIngrRecipeDialog(); break;
        case 12: applyIngrRecipeAssoc(); break;
        case 13: removeIngr(); break;
        case 14: checkBoxNoUnitIngredient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: checkBoxNoUnitIngredient(); break;
        case 16: openAddCookStep(); break;
        case 17: addUnit(); break;
        case 18: removeUnit(); break;
        case 19: openManageUnities(); break;
        case 20: closeManageUnitiesDialog(); break;
        case 21: addNewUnitMethod(); break;
        case 22: removeOldUnitMethod(); break;
        case 23: removeAllUnitiesMethod(); break;
        case 24: openAddMaterial(); break;
        case 25: closeAddMaterialDialog(); break;
        case 26: removeActionMaterial(); break;
        case 27: addActionMaterial(); break;
        case 28: openManageActions(); break;
        case 29: getSelectedMaterial(); break;
        case 30: closeManageActions(); break;
        case 31: addActionMaterial2(); break;
        case 32: removeActionMaterial2(); break;
        case 33: toggleActionToMaterial2((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 34: applyManageActions(); break;
        case 35: addNewActionMethod(); break;
        case 36: addMaterialMethod(); break;
        case 37: getMaterialFromActionRefresh(); break;
        case 38: closeAddStepDialog(); break;
        case 39: addCookStepMethod(); break;
        case 40: removeStepToRecipe(); break;
        case 41: submitRecipeMethod(); break;
        case 42: openRecipe(); break;
        default: ;
        }
        _id -= 43;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
