SBA Message Action is a webform-enabled and webform-user-enabled node type for "contact your congressperson"
type messages, which can also include non-legislator custom targets.

The message action node consists of title, image, call-to-action and body fields,
the body being an extended description of the action. There are also two associated taxonomies,
one to match the expected subject fields on congressional contact forms, and another to
categorize the actions according to the client's preferred categories. Webform component fields
are also attached to the message action to collect visitor names and and addresses.

After creating a new Message Action node, administrators are redirected to the messages tab,
where they are prompted to create a message to attach to the Message Action webform.
Message targets (recipients) are added during this message creation process. Multiple messages
with multiple targets can be attached to a single Message Action webform.

The messages are Entity API entities attached to the message actions via entity references. The targets
are stored on the Advocacy API server. This module will not fully function without a valid, configured API account.
API configuration is handled by the Springboard Advocacy module.
