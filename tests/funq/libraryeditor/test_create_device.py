#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Test creating a device with the library editor
"""


def test(library_editor, helpers):
    """
    Create new device
    """

    # Open "New Library Element" wizard
    library_editor.action('libraryEditorActionNewElement').trigger(blocking=False)

    # Choose type of element
    library_editor.widget('libraryEditorNewElementWizardChooseTypeDeviceButton').click()

    # Enter metadata
    widget_properties = {
        ('NameEdit', 'text'): 'New Device',
        ('DescriptionEdit', 'text'): 'Foo Bar',
        ('KeywordsEdit', 'text'): '',
        ('AuthorEdit', 'text'): 'Functional Test',
        ('VersionEdit', 'text'): '1.2.3',
    }
    for (widget, property), value in widget_properties.items():
        library_editor.widget('libraryEditorNewElementWizardMetadata' + widget).set_property(property, value)
    library_editor.widget('libraryEditorNewElementWizardNextButton').click()

    # Select component
    library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChooseComponentButton').click(blocking=False)
    category_tree = library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChooseComponentDialogCategoriesTree')
    helpers.wait_for_model_items_count(category_tree, 1)
    category_tree.model_items().items[0].select()
    components_list = library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChooseComponentDialogComponentsList')
    helpers.wait_for_model_items_count(components_list, 1)
    components_list.model_items().items[0].select()
    library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChooseComponentDialogAcceptButton').click()

    # Select package
    library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChoosePackageButton').click(blocking=False)
    category_tree = library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChoosePackageDialogCategoriesTree')
    helpers.wait_for_model_items_count(category_tree, 3)
    category_tree.model_items().items[2].select()
    packages_list = library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChoosePackageDialogPackagesList')
    helpers.wait_for_model_items_count(packages_list, 1)
    packages_list.model_items().items[0].select()
    library_editor.widget('libraryEditorNewElementWizardDevicePropertiesChoosePackageDialogAcceptButton').click()

    # Finish
    dialog = library_editor.widget('libraryEditorNewElementWizard')
    library_editor.widget('libraryEditorNewElementWizardFinishButton').click()
    helpers.wait_until_widget_hidden(dialog)
