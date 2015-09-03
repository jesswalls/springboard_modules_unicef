Provides a message entity for use by sba action modules. Does nothing on its own without a parent node module.

Allows message target (recipient) selection for messages using a views exposed filter search
combined with some javascript, which helps insert the target data into the entity's
serialized data field.

Also saves message/target data to the API server, including a unique ID for both
the parent action node and the message entity.

Based on the example entity module found here: https://www.drupal.org/project/model

This module is capable of handling multiple message entity types.
Message types are defined in the sba_message_type table, and individual
entities are stored in the sba_message table.

Currently there is one message type, SBA Message Action Message, which is used by the Sba
Message Action module, and which is related to message action nodes via the
entity reference module.