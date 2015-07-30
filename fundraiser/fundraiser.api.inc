<?php

/**
 * @file
 * Provides documentation of available fundraiser hooks.
 */

/**
 * IMPLEMENTATION NOTES:
 *
 * The exact implementation of a donor form as displayed to a user to
 * place a donation has been moved to an exterior module. (currently webform).
 * So long as we are using an exterior module to display the form we want,
 * the exact details will be handled by a glue module to link fundraiser
 * to whatever display implementation we use. This allows us future
 * flexibility and separation of concerns in code.
 *
 * As a result this module does not form_alter webform forms.
 * That's the glue's job. It also means that picking the workflow back up
 * of processing a donation is by executing a process call in fundraiser
 * from the submit in the glue module. So if you don't see a straight path
 * from one to the other in this module it's because the control of flow goes
 * into the glue module before coming back here.
 *
 * Donations themselves are also tracked in an exterior module
 * (currently commerce). A glue module is provided for this as well.
 * Donations are stored as orders in Commerce, and the glue module translates.
 * So the exterior module handling the purchasing stage of things is the one
 * that needs to be aware of things like states, user info, and the like.
 * To allow multiple gateways to be used depending on the fundraiser, fundraiser
 * does interact with a list of available gateways for use during processing.
 *
 * In practice this means, exterior modules are blind to each other,
 * and fundraiser is blind to them. The glue modules between them are the
 * only systems aware of more than one module at a time.
 */

/**
 * Available fundraiser hooks.
 */

/**
 * Provide additional replacement methods for _fundraiser_replace_token().
 *
 * For all modules.
 *
 * @return string
 *   Return the token replaced message string.
 */
function hook_fundraiser_replace_tokens($message, $donation) {

}

/**
 * Get the field info array for fields that fundraiser is expecting.
 *
 * For all modules.
 *
 * This is used by display and charge glue modules to track field information
 * and provide callbacks for formatting.
 *
 * @return array
 *   Return an info array.
 */
function hook_fundraiser_field_info() {

}

/**
 * Get the field info array for fields that fundraiser is expecting.
 *
 * For all modules.
 *
 * This is used by display and charge glue modules to track field information
 * and provide callbacks for formatting.
 *
 */
function hook_fundraiser_field_info_alter(&$info) {

}

/**
 * If display is handled in a non-standard form array, get the requested field.
 *
 * For display glue modules.
 *
 * @return array
 *   Return a field definition as per normal form arrays.
 */
function hook_fundraiser_get_form_field($form, $field_key) {

}

/**
 * If display is handled in a non-standard form array, update the field.
 *
 * For display glue modules.
 *
 * @return array
 *   Return the updated form. (Yes, all of the form).
 */
function hook_fundraiser_update_form_field($form, $field_key) {

}

/**
 * Alter client side validation of webform fields.
 *
 * Fundraiser uses jQuery validation rules to handle client side validation
 * of fields like zipcode, CVV, and card number. Implement this hook in your
 * module to modify or extend these rules.
 *
 * Available validators:
 *   required: "This field is required",
 *   remote: "Please fix this field",
 *   email: "Enter a valid email address",
 *   url: "Enter a valid URL",
 *   date: "Enter a valid date",
 *   dateISO: "Enter a valid date (ISO)",
 *   number: "Must be a number", // changed
 *   digits: "Enter only digits",
 *   creditcard: "Enter a valid credit card number",
 *   equalTo: "Enter the same value again",
 *   accept: "Enter a value with a valid extension",
 *   maxlength: jQuery.validator.format("Enter no more than {0} characters"),
 *   minlength: jQuery.validator.format("Enter at least {0} characters"),
 *   rangelength: jQuery.validator.format("Enter a value between {0} and {1} characters long"),
 *   range: jQuery.validator.format("Enter a value between {0} and {1}"),
 *   max: jQuery.validator.format("Enter a value less than or equal to {0}"),
 *   min: jQuery.validator.format("Enter a value greater than or equal to {0}")
 *
 * Note: the "messages" property stores the return message to display if a
 * validator check fails.
 *
 * Example ruleset:
 * $settings['card_cvv'] = (object) array(
 *   'required' => TRUE,
 *   'number' => TRUE,
 *   'minlength' => 3,
 *   'maxlength' => 4,
 *   'messages' => (object) array(
 *     'required' => t('This field is required.'),
 *     'number' => t('Must be a number.'),
 *     'minlength' => t('Minimum of 3 characters.'),
 *     'maxlength' => t('Maximum of 4 characters.'),
 *    ),
 *  );
 */
function hook_fundraiser_donation_form_js_validation_alter(&$settings) {

}

/**
 * Provide any additional changes for the donation form display.
 *
 * For display glue modules.
 *
 * Called in fundraiser_donation_form(), which must be called from the
 *   display module to display the donation form.
 *
 * @return array
 *   Return form.
 */
function hook_fundraiser_donation_form($form, $field_key) {

}

/**
 * Provide validation for the donation form.
 *
 * For display glue modules.
 *
 * @return array
 *   An array with a 'nid' key of the node being validated if it failed
 *   validation.
 */
function hook_fundraiser_donation_validate($form, $form_state) {

}

/**
 * Provide submission handling for the donation form.
 *
 * For display glue modules.
 *
 * @return void
 *   Return nothing, but update the donation object with submitted values
 *   per field information keys.
 */
function hook_fundraiser_donation_submit($form, $form_state, $donation) {

}

/**
 * Handle any post submission behaviors as needed.
 *
 * For all modules.
 */
function hook_fundraiser_donation_post_submit_alter(&$form, &$form_state, &$donation) {

}

/**
 * Handle any post failed validation behaviors.
 *
 * For all modules.
 */
function hook_fundraiser_donation_failed_validation($errors) {

}

/**
 * Add any additional data before attenpting to create the donation.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the donation object with data.
 */
function hook_fundraiser_donation_create_add_data($donation) {

}

/**
 * Create the donation in the system used to track donations and charges.
 *
 * For charge glue modules.
 *
 * @return void
 *   Return nothing, but update the donation object with data.
 */
function hook_fundraiser_donation_create($donation) {

}

/**
 * Last chance to add data to the donation before updating it.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the donation object with data.
 */
function hook_fundraiser_donation_update($donation) {

}

/**
 * Attempt to charge the donation.
 *
 * For charge glue modules.
 *
 * @return void
 *   Return nothing, but update the donation object with success results.
 */
function hook_fundraiser_donation_process($donation, $charge_function) {

}

/**
 * Respond to a successful donation.
 *
 * For all modules.
 */
function hook_fundraiser_donation_success($donation) {

}

/**
 * Respond to a declined donation.
 *
 * For all modules.
 */
function hook_fundraiser_donation_decline($donation) {

}

/**
 * Respond to an excepted donation.
 *
 * For all modules.
 *
 * @todo Determine where this is called.
 */
function hook_fundraiser_donation_exception($donation) {

}

/**
 * Respond to a cancelled donation.
 *
 * For all modules.
 */
function hook_fundraiser_donation_cancel($donation) {

}

/**
 * Attempt to process a refund.
 *
 * For charge glue modules.
 *
 * @return void
 *   Return nothing, but update the donation object with success results.
 */
function hook_fundraiser_donation_refund($donation, $refund_function) {

}

/**
 * Respond to a successful refund.
 *
 * For all modules.
 */
function hook_fundraiser_donation_refund_success($donation) {

}

/**
 * Respond to a declined refund.
 *
 * For all modules.
 */
function hook_fundraiser_donation_refund_decline($donation) {

}

/**
 * Add additional data to the donation object.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the donation object with results.
 */
function hook_fundraiser_donation_get_donation($donation) {

}

/**
 * Provide available gateway information for all gateways.
 *
 * For all modules.
 */
function hook_fundraiser_gateway_info() {

}

/**
 * Provide available gateway information for all gateways.
 *
 * For all modules.
 */
function hook_fundraiser_gateway_info_alter(&$gateways) {

}

/**
 * Respond to the creation of a fundraiser type node.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the fundraiser object with results.
 */
function hook_fundraiser_create_fundraiser_alter($fundraiser) {

}

/**
 * Add additional data to the fundraiser object.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the fundraiser object with results.
 */
function hook_fundraiser_get_fundraiser_alter($fundraiser) {

}

/**
 * Add additional data to the fundraiser object.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the fundraiser object with results.
 */
function hook_fundraiser_update_fundraiser_alter($fundraiser) {

}

/**
 * Add additional data to the fundraiser object.
 *
 * For all modules.
 *
 * @return void
 *   Return nothing, but update the fundraiser object with results.
 */
function hook_fundraiser_delete_fundraiser_alter($fundraiser) {

}

/**
 * Allow gateway information to be updated or changed.
 *
 * For all modules.
 *
 * Return gateway information from a given donation.
 */
function hook_fundraiser_get_donation_gateway($did, $gateway) {

}

/**
 * An example donation object. This is the object returned when you request
 * a donation object. It is built by hooks that query the various sub
 * and glue modules, and is cached at that time.
 *
 * Use this object to gather all your values that may be needed during
 * donation processing. It is worth noting, all fields under [donation]
 * are keyed according to the field information provided by the fundraiser
 * field api.
 *
 * stdClass Object
 *
 *    [did] => 1
 *    [nid] => 1
 *    [node] => stdClass Node Object
 *    [uid] => 1
 *    [user] => stdClass User Object
 *    [gateway] => Array
 *        (
 *            [title] => Test Gateway
 *            [description] => Process credit card payments
 *                             through the Test Gateway.
 *            [credit] => test_gateway_charge
 *            [id] => test_gateway
 *            [enabled] => 1
 *        )
 *    [txn_id] => ''
 *    [payment] => Array
 *        (
 *            [receipt_id] => ''
 *            [receipt_date] => ''
 *            [refund_summary] => ''
 *            [refunded_total] => ''
 *        )
 *    [donation] => Array
 *        (
 *            [recurs_monthly] => ''
 *            [amount] => 10
 *            [other_amount] => ''
 *            [first_name] => firstname
 *            [last_name] => lastname;
 *            [mail] => example@example.com
 *            [address] => address1
 *            [address_line_2] => address2
 *            [city] => city
 *            [country] => 840
 *            [state] => 15
 *            [zip] => 12345
 *            [card_number] => 1111
 *            [card_expiration_month] => 6
 *            [card_expiration_year] => 2012
 *            [card_cvv] => ''
 *            [cc_type] => visa
 *        )
 *    [status] => failed
 *    [last_changed] => timestamp
 *    [data] => Array
 *        (
 *            [cc_data] => <encrypted cc data string>
 *            [txn_type]=> reference_txn
 *            [ref_id] => ''
 *        )
 *
 */

/**
 * The fundraiser field API is an additional API that focuses on the creation,
 * handling and updating of fields in the fundraiser system. Since both
 * field display and charge processing are agnostic in this system,
 * we need a central location through which information about the fields
 * fundraiser expects may flow. The field_info array is it. Fundraiser builds
 * the array from it's own information and any information presented to it
 * by other modules. Other modules also have the opportunity to add validation
 * and submit routines for each of these fields, and will have access to the
 * submitted results according to the field keys given. This system is the
 * backbone of how one glue module may speak to and interact with the other.
 *
 * The #create_callback is used for fields whose settings are dependant
 * on the values given during field creation. For example, the amount field
 * could be displayed as a select box or as a text field depending on
 * fundraiser's settings. So the field callback checks during field creation
 * based on the associated fundraiser node to determine which.
 *
 * The #display_callback is an additional callback to allow another module
 * to override display from the glue module. This is useful if another module
 * can provide a more focused implementation of the form element than the
 * glue module can. For example, the charging module may be more aware of
 * available countries/states than the glue module, and can override
 * the creation and display to match this allowing for an AJAX interface.
 */

/**
 * An example field info structure. This array allows modules to check with
 * fundraiser regarding any fields it thinks it needs. Use this array to
 * generate forms, submit results, or tell other modules how to generate,
 * display, or validate your own fields.
 *
 * Array
 * (
 *   [donation] => Array
 *       (
 *           [#title] => Donation
 *           [#type] => fieldset
 *           [#required] => 0
 *           [amount] => Array
 *               (
 *                   [#title] => Amount
 *                   [#type] => textfield
 *                   [#required] => 1
 *                   [#extra] => Array
 *                       (
 *                           [description] => ''
 *                           [width] => 10
 *                           [field_prefix] => $
 *                       )
 *
 *
 *   [#create_callback] => _fundraiser_amount_field_create
 *               )
 *
 *
 *   [other_amount] => Array
 *               (
 *                   [#title] => Other
 *                   [#type] => textfield
 *                   [#required] => 0
 *                   [#extra] => Array
 *                       (
 *                           [description] => Minimum payment $10.
 *                           [width] => 10
 *                           [field_prefix] => $
 *                       )
 *
 *
 *   [#create_callback] => _fundraiser_other_amount_field_create
 *                   [#display_callback] => ''
 *                   [#validate_callback] =>
 *                                      _fundraiser_other_amount_field_validate
 *               )
 *
 *   )
 * )
 *
 */

/**
 * General purpose getting total donation amount for an array of nids.
 *
 * Does not take multiple currencies into account.  Assumes all USD.
 *
 * Although this is a hook, the calling function only uses the first
 *   implementation it finds.  For almost all cases this should be
 *   fundraiser_commerce_fundraiser_get_total_donations_by_nids().
 *
 * This documentation is here for completeness, but you generally should not
 *   implement this hook.
 *
 * @param array $nids
 *   Node IDs.
 * @param int|bool $start
 *   Start timestamp or FALSE for no range.
 * @param int|bool $end
 *   End timestamp or FALSE for no range..
 *
 * @return float
 *   Total amount of donations.
 */
function hook_fundraiser_get_total_donations_by_nids($nids, $start, $end) {

}
