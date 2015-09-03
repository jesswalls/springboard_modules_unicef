Springboard Advocacy is a suite of modules which facilitate online activism.

Submodules include Springboard Petition and Springboard Message Action.

Springboard Advocacy communicates with the Springboard Advocacy Server via
a PHP SDK which lives in the Drupal libraries folder. The remote advocacy server stores the targets
of advocacy actions and sends advocacy messages to them. An Advocacy API account is required for this
functionality. Springboard Petition will function without an API account, but the Message Action module
absolutely requires a valid, configured API account's Oauth credentials to function fully.

The Springboard Advocacy module acts as a bridge between its submodules and the Advocacy server.
It provides configuration and common functions for the submodules, including;

* An SDK loader class which handles Advocacy Server Oauth Token retrieval and creation, as well
as initializing the SDK client object used for API calls within modules.

* Communication with the Smarty Streets API to verify addresses and retrieve 9 digit zip codes.

* Processing webform submissions and preparing them for submission to the API server

* A views-driven admin dashboard for the submodule content types.

* Views integration with the Advocacy API server, including a custom query plugin, a custom cache plugin,
a custom pager plugin, field handlers and filter handlers used in views owned by advocacy submodules.

Configure Springboard Advocacy's API settings at at http://[site-name]/admin/config/services/advocacy